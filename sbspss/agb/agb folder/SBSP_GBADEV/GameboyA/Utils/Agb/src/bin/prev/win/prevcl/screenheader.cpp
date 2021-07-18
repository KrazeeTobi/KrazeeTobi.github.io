//======================================================
//    screenheader.cpp                                   
//    Header chunk
//                                                      
//    Copyright (C) 1999,NINTENDO Co.,Ltd.             
//======================================================

#include <iostream>
#include <fstream>
#include <list>
#include <agbtypes.h>

#include "ex_reference.h"
#include "agbnode.h"
#include "token_list.h"
#include "nodeinfo.h"
#include "prev_util.h"
#include "screenheader.h"
#include "c_access.h"
#include "ndbackground.h"
#include "ndimage.h"
#include "nodemanager.h"
//----------------------------------------------------------------------
__MAGBX__START
//----------------------------------------------------------------------
bool ScreenHeader::parse_member( TokenList& token_list ,
				const std::string& identifier)
{
    bool ret_value = false;
    if( identifier == "Objects" )
    {
	ret_value = parse_objects(token_list);
    }
    if( identifier == "ObjectPalette" )
    {
	ret_value = parse_object_palette(token_list);
    }
    if( identifier == "BGs" )
    {
	ret_value = parse_bgs(token_list);
    }
    if( identifier == "BGPalette" )
    {
	ret_value = parse_bg_palette(token_list);
    }
    if( identifier == "BGColor" )
    {
	ret_value = parse_bg_color( token_list );
    }
    return ret_value;
}
//----------------------------------------------------------------------
bool ScreenHeader::parse_objects( TokenList& token_list )
{
    std::string tmp_str;
    u32 parse_num = 0;
    NodeInfo* info_ptr;
    while( 1 )
    {
	tmp_str = "";
	if( (IsNextSemicolon( token_list ) == true)
	 || ( false == ParseString( token_list,tmp_str) ) )
	{
	    if( 0 == parse_num )
	    {
		return false;
	    }
	    return true;
	}
	info_ptr = new NodeInfo( m_node_magic_ptr ,
				 m_node_manager_ptr);
	if( NULL == info_ptr )
	{
	    return false;
	}
	info_ptr->SetNodeName( tmp_str );
	m_object_list.push_back( info_ptr );
	++parse_num;
    }
	//  It will not be here.
    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::parse_bgs( TokenList& token_list )
{
    std::string tmp_str;
    u32 parse_num = 0;
    NodeInfo* info_ptr;
    while( 1 )
    {
	tmp_str = "";
	if( (IsNextSemicolon( token_list ) == true)
	 || ( false == ParseString( token_list,tmp_str) ) )
	{
	    if( 0 == parse_num )
	    {
		return false;
	    }
	    return true;
	}
	info_ptr = new NodeInfo( m_node_magic_ptr ,
				 m_node_manager_ptr);
	if( NULL == info_ptr )
	{
	    return false;
	}
	info_ptr->SetNodeName( tmp_str );
	m_bg_list.push_back( info_ptr );
	++parse_num;
    }
	//  It will not be here.
    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::parse_object_palette( TokenList& token_list )
{
    std::string tmp_str;
    u32 parse_num = 0;
    if( false == ParseString( token_list,tmp_str) )
    {
	return false;
    }
    m_object_palette.SetNodeName( tmp_str );
    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::parse_bg_palette( TokenList& token_list )
{
    std::string tmp_str;
    u32 parse_num = 0;
    if( false == ParseString( token_list,tmp_str) )
    {
	return false;
    }
    m_bg_palette.SetNodeName( tmp_str );
    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::parse_bg_color( TokenList& token_list )
{
    u8 red,green,blue;
    u32 parse_num = 0;
    if( false == ParseValue( token_list,red) )
    {
	return false;
    }
    if( false == ParseValue( token_list,green) )
    {
	return false;
    }
    if( false == ParseValue( token_list,blue) )
    {
	return false;
    }
    m_bg_color.Set( red,green,blue );
    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::set_bg_cnt( u16& bg_cnt, u8 bg_number )
{
    NodeInfo *character_ptr;
    AGBNode* bg_ptr;
    AGBNode* bg_ch_ptr;
    u16 width,height;
    u8 bit_count;
    bg_ptr = m_node_manager_ptr->GetNodePtr( m_info_ptr[bg_number]->GetID() );
    if( NULL == bg_ptr )
    {
	std::cerr << "\"" << m_info_ptr[bg_number]->GetNodeName().c_str();
	std::cerr << "\" reading failure" << std::endl;
    }
    if( false == bg_ptr->GetValue( &character_ptr,
				   NDBG_VALUE_MAP_CHARACTER,
				   0, 1 ) )
    {
	return false;
    }
    if( NULL == character_ptr )
    {
	ErrorMessage( "There is a problem with image parameter.");
	return false;
    }
    if( false == bg_ptr->GetValue( &width,
				   NDBG_VALUE_VRAM_SIZE,
				   0, 1 ) )
    {
	ErrorMessage( "There is a problem with image parameter.");
	return false;
    }
    if( false == bg_ptr->GetValue( &height,
				   NDBG_VALUE_VRAM_SIZE,
				   1, 1 ) )
    {
	ErrorMessage( "There is a problem with image parameter.");
	return false;
    }

    bg_ch_ptr = m_node_manager_ptr->GetNodePtr( character_ptr->GetID() );
    if( NULL == bg_ch_ptr )
    {
	return false;
    }
    if( false == bg_ch_ptr->GetValue( &bit_count,
				      NDIMAGE_VALUE_ID_BIT_COUNT,
				      0,1 ) )
    {
	ErrorMessage( "There is a problem with image parameter.");
	return false;
    }
    bg_cnt = 0;
    if( bit_count == 8 )
    {
	bg_cnt |= 0x0080;
    }

	//  scaling/rotation mode
    if( (m_bg_mode > 0) && (bg_number >= 2) )
    {
	if( width != height )
	{
	    ErrorMessage( "Width or height of BG is irregular.");
	    return false;
	}
	bg_cnt |= 0x2000;
	switch( width )
	{
	case 128 :
	    break;
	case 256 :
	    bg_cnt |= 0x4000;
	    break;
	case 512 :
	    bg_cnt |= 0x8000;
	    break;
	case 1024 :
	    bg_cnt |= 0xc000;
	    break;
	default :
	    ErrorMessage( "Width or height of BG is irregular.");
	    return false;
	}
    }
    else	//  text mode
    {
	switch( width )
	{
	case 256 :
	    switch( height )
	    {
	    case 256 :
		break;
	    case 512 :
		bg_cnt |= 0x8000;
		break;
	    default :
		ErrorMessage( "Width or height of BG is irregular.");
		return false;
	    }
	    break;
	case 512 :
	    switch( height )
	    {
	    case 256 :
		bg_cnt |= 0x4000;
		break;
	    case 512 :
		bg_cnt |= 0xc000;
		break;
	    default :
		return false;
		ErrorMessage( "Width or height of BG is irregular.");
	    }
	    break;
	default :
	    ErrorMessage( "Width or height of BG is irregular.");
	    return false;
	}
    }
    bg_cnt |= (u16)(m_priority[bg_number] & 0x3);
    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::create_disp_header( void )
{
    if( m_bg_mode == 255 )
    {
	if( false == attach_bg_number() )
	{
	    return false;
	}
    }
    u16 bg_disp_flag = 0;
    if( m_info_ptr[0] != NULL )
    {
	bg_disp_flag |= 1;
	if( false == set_bg_cnt( m_bg0_cnt, 0 ) )
	{
	    return false;
	}
    }
    if( m_info_ptr[1] != NULL )
    {
	bg_disp_flag |= 2;
	if( false == set_bg_cnt( m_bg1_cnt, 1 ) )
	{
	    return false;
	}
    }
    if( m_info_ptr[2] != NULL )
    {
	bg_disp_flag |= 4;
	if( false == set_bg_cnt( m_bg2_cnt, 2 ) )
	{
	    return false;
	}
    }
    if( m_info_ptr[3] != NULL )
    {
	bg_disp_flag |= 8;
	if( false == set_bg_cnt( m_bg3_cnt, 3 ) )
	{
	    return false;
	}
    }
	//  Set DispCnt
    m_disp_cnt = 0x1040;
    m_disp_cnt |= (bg_disp_flag << 8);
    m_disp_cnt |= (u16)m_bg_mode;

    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::attach_bg_number(void)
{
    volatile u8 sr_number;
    volatile u8 tx_number;
    u8 priority = 0;
    NodeInfo* image_ptr;
    AGBNode*  bg_ptr;
    AGBNode*  bg_image_ptr;
    u8 bit_count;
    sr_number = 2;
    tx_number = 0;
    std::list<NodeInfo*>::iterator bg_it;
    for(bg_it = m_bg_list.begin() ;
	bg_it != m_bg_list.end() ;
	++bg_it )
    {
	bg_ptr = m_node_manager_ptr->GetNodePtr( (*bg_it)->GetID() );
	if( NULL == bg_ptr )
	{
	    std::cerr << "\"" << (*bg_it)->GetNodeName().c_str() << "\"";
	    std::cerr << "failed to read" << std::endl;
	}
	if( false == bg_ptr->GetValue( &image_ptr, NDBG_VALUE_MAP_IMAGE,
					0, 1 ) )
	{
	    return false;
	}
	if( NULL == image_ptr )
	{
	    return false;
	}
	bg_image_ptr = m_node_manager_ptr->GetNodePtr( image_ptr->GetID() );
	if( NULL == bg_image_ptr )
	{
	    return false;
	}
	if( false == bg_image_ptr->GetValue( &bit_count,
					     NDIMAGE_VALUE_ID_BIT_COUNT,
					     0,1 ) )
	{
	    return false;
	}
	    //  If scaling/rotation mode,
	if( bit_count == 8 )
	{
	    if( sr_number >= 4 ) return false;
	    if( tx_number >= 3 ) return false;
	    m_info_ptr[sr_number] = (*bg_it);
	    m_priority[sr_number] = priority;
	    ++sr_number;
	    ++priority;
	    continue;
	}
	    //  If scaling/rotation mode,
	if( bit_count == 16 )
	{
	    if( tx_number >= 4 ) return false;
	    if( sr_number >= 4 ) return false;
	    if( sr_number == 3 )
	    {
		if( tx_number >= 2 ) return false;
	    }
	    m_info_ptr[tx_number] = (*bg_it);
	    m_priority[tx_number] = priority;
	    ++tx_number;
	    ++priority;
	    continue;
	}
	return false;
    }
    m_bg_mode = (sr_number == 2) ? 0 :
		((tx_number == 0) ? 2 : 1) ;
    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::output_disp_header( std::ofstream& out )
{
    if( false == create_disp_header() )
    {
	return false;
    }
    if( false == ::Output( out , m_disp_cnt ) ) return false;
    if( false == ::Output( out , m_bg0_cnt ) ) return false;
    if( false == ::Output( out , m_bg1_cnt ) ) return false;
    if( false == ::Output( out , m_bg2_cnt ) ) return false;
    if( false == ::Output( out , m_bg3_cnt ) ) return false;
    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::output_objects( std::ofstream& out )
{
	//  Output default palette
    if( false == m_object_palette.Output(out) )
    {
	return false;
    }
	//  Output object number   
    if( false == ::Output( out , (u16)m_object_list.size() ) )
    {
	return false;
    }
    std::list<NodeInfo*>::iterator object_it;
    for( object_it = m_object_list.begin() ;
	 object_it != m_object_list.end() ;
	 ++object_it )
    {
	if( NULL == *object_it )
	{
	    return false;
	}
	if( false == (*object_it)->Output( out ) )
	{
	    return false;
	}
    }
    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::output_bgs( std::ofstream& out )
{
	//  Output default palette 
    if( false == m_bg_palette.Output(out) )
    {
	return false;
    }
	//  Output object number
    if( false == ::Output( out , (u16)m_bg_list.size() ) )
    {
	return false;
    }
    int i;
    u16 priority_map = 0;
    for( i=0 ; i<4 ; ++i )
    {
	priority_map <<= 4;
	priority_map |= m_priority[i] & 0x0f;
    }
    ::Output(out, priority_map );
    ::Output(out,m_bg_color.Get() );
    for( i=0; i<4; ++i )
    {
	if( NULL == m_info_ptr[i] )
	{
	    ::Output( out, (u32)0xffffffff );
	}
	else
	{
	    if( false == m_info_ptr[i]->Output( out ) )
	    {
		return false;
	    }
	}
    }
    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::outtxt_objects( std::ofstream& out )
{
    if( false == out.is_open() ) return false;

    out << "ObjectPalette";

    if( false == m_object_palette.Outtxt(out) )
    {
	return false;
    }
    out << ";" << std::endl;

    out << "Objects";
    std::list<NodeInfo*>::iterator object_it;
    for( object_it = m_object_list.begin() ;
	 object_it != m_object_list.end() ;
	 ++object_it )
    {
	if( NULL == *object_it )
	{
	    return false;
	}
	if( false == (*object_it)->Outtxt( out ) )
	{
	    return false;
	}
	out << "," << std::endl;
    }
    out << ";" << std::endl;
    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::outtxt_bgs( std::ofstream& out )
{
    if( false == out.is_open() ) return false;

    out << "BGPalette";

    if( false == m_bg_palette.Outtxt(out) )
    {
	return false;
    }
    out << ";" << std::endl;

    out << "BGs";
    std::list<NodeInfo*>::iterator bg_it;
    for( bg_it = m_bg_list.begin() ;
	 bg_it != m_bg_list.end() ;
	 ++bg_it )
    {
	if( NULL == *bg_it )
	{
	    return false;
	}
	if( false == (*bg_it)->Outtxt( out ) )
	{
	    return false;
	}
	out << "," << std::endl;
    }
    out << ";" << std::endl;

    out << "BGColor ";
    if( false == ::Outtxt( out, m_bg_color.Red() ) )
    {
	return false;
    }
    if( false == ::Outtxt( out, m_bg_color.Green() ) )
    {
	return false;
    }
    if( false == ::Outtxt( out, m_bg_color.Blue() ) )
    {
	return false;
    }
    out << ";" << std::endl;
    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::out_c_source_disp_header( std::ofstream& out )
{
    if( false == create_disp_header() )
    {
	return false;
    }
    out << "const " << GetDispHeaderStructName().c_str() << " ";
    out << GetDispHeaderName().c_str() << " = {" << std::endl;
    if( false == ::Outtxt( out , m_disp_cnt ) ) return false;
    out << "," << "\t// DISPCNT" << std::endl;
    if( false == ::Outtxt( out , m_bg0_cnt ) ) return false;
    out << "," << "\t// BG0CNT" << std::endl;
    if( false == ::Outtxt( out , m_bg1_cnt ) ) return false;
    out << "," << "\t// BG1CNT" << std::endl;
    if( false == ::Outtxt( out , m_bg2_cnt ) ) return false;
    out << "," << "\t// BG2CNT" << std::endl;
    if( false == ::Outtxt( out , m_bg3_cnt ) ) return false;
    out << "," << "\t// BG3CNT" << std::endl;
    out << "};" << std::endl;
    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::out_c_source_objects( std::ofstream& out )
{
    if( false == out.is_open() )
    {
	return false;
    }

	//  Output array of object 
    out << std::endl;
    out << "const u32 " << GetCName().c_str() << "_Table[";
    out << GetNumOfObjects() << "] = {" << std::endl;

    std::list<NodeInfo*>::iterator object_it;
    for( object_it = m_object_list.begin() ;
	 object_it != m_object_list.end() ;
	 ++object_it )
    {
	if( NULL == *object_it )
	{
	    return false;
	}
	if( false == (*object_it)->OutCSource( out ) )
	{
	    return false;
	}
	out << "," << std::endl;
    }
    out << "};" << std::endl;

    out << std::endl;
    out << "const " << GetCStructName().c_str() << " ";
    out << GetCName().c_str() << " = {" << std::endl;
    if( false == m_object_palette.OutCSource(out) )
    {
	OutputError( "Default palette does not exist." );
	return false;
    }
    out << "," << std::endl;
    out << GetNumOfObjects() << "," << std::endl;

    out << "(u32*)" << GetCName().c_str() << "_Table" << std::endl;
    out << "};" << std::endl;

    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::out_c_source_bgs( std::ofstream& out )
{
    if( false == out.is_open() )
    {
	return false;
    }

    out << std::endl;
    out << "const " << GetCStructName_BG().c_str() << " ";
    out << GetCName_BG().c_str() << " = {" << std::endl;
    if( false == m_bg_palette.OutCSource(out) )
    {
	OutputError( "Default palette does not exist." );
	return false;
    }
    out << "," << std::endl;
    out << GetNumOfBGs() << "," << std::endl;
    int i;
    u16 priority_map = 0;
    for( i=0 ; i<4 ; ++i )
    {
	priority_map <<= 4;
	priority_map |= m_priority[i] & 0x0f;
    }
    ::Outtxt(out, priority_map );
    out << "," << std::endl;
    ::Outtxt(out, m_bg_color.Get() );
    out << "," << std::endl;
    out << "{" << std::endl;
    for( i=0 ; i<4 ; ++i )
    {
	if( NULL == m_info_ptr[i] )
	{
	    out << "0xffffffff";
	}
	else
	{
	    if( false == m_info_ptr[i]->OutCSource(out) )
	    {
		return false;
	    }
	}
	out << "," << std::endl;
    }
    out << "}" << std::endl;
    out << "};" << std::endl;

    return true;
}
//----------------------------------------------------------------------
ScreenHeader::~ScreenHeader()
{
    std::list<NodeInfo*>::iterator object_it;
    for(object_it = m_object_list.begin() ;
	object_it != m_object_list.end() ;
	++object_it )
    {
	delete *object_it;
    }
    for(object_it = m_bg_list.begin() ;
	object_it != m_bg_list.end() ;
	++object_it )
    {
	delete *object_it;
    }
}
//----------------------------------------------------------------------
std::string ScreenHeader::GetCStructName( void )
{
    std::string ret_str( "nodeRootObjects" );
    return ret_str;
}
//----------------------------------------------------------------------
std::string ScreenHeader::GetCStructName_BG( void )
{
    std::string ret_str( "nodeRootBGs" );
    return ret_str;
}
//----------------------------------------------------------------------
std::string ScreenHeader::GetDispHeaderName(void)
{
    std::string ret_name("DefaultDispHeader");
    return ret_name;
}
//----------------------------------------------------------------------
std::string ScreenHeader::GetDispHeaderStructName(void)
{
    std::string ret_name("nodeDispHeader");
    return ret_name;
}
//----------------------------------------------------------------------
std::string ScreenHeader::GetCName(void)
{
    std::string ret_name("RootObjects");
    return ret_name;
}
//----------------------------------------------------------------------
std::string ScreenHeader::GetCName_BG(void)
{
    std::string ret_name("RootBGs");
    return ret_name;
}
//----------------------------------------------------------------------
u32 ScreenHeader::GetNumOfObjects(void)
{
    return (u32)m_object_list.size();
}
//----------------------------------------------------------------------
u32 ScreenHeader::GetNumOfBGs(void)
{
    return (u32)m_bg_list.size();
}
//----------------------------------------------------------------------
u32 ScreenHeader::GetDispHeaderSize(void)
{
    return 10;
}
//----------------------------------------------------------------------
u32 ScreenHeader::GetSize(void)
{
    return GetObjectsSize() + GetBGsSize() + GetDispHeaderSize();
}
//----------------------------------------------------------------------
u32 ScreenHeader::GetObjectsSize(void)
{
    return (u32)((4*GetNumOfObjects())+6);
}
//----------------------------------------------------------------------
u32 ScreenHeader::GetBGsSize(void)
{
    return (u32)((4*4)+8);
}
//----------------------------------------------------------------------
bool ScreenHeader::Output( std::ofstream& out )
{
    if( false == output_disp_header(out) )
    {
	return false;
    }
    if( false == output_objects(out) )
    {
	return false;
    }
    if( false == output_bgs(out) )
    {
	return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::Outtxt( std::ofstream& out )
{
    if( false == outtxt_objects(out) )
    {
	return false;
    }
    if( false == outtxt_bgs(out) )
    {
	return false;
    }
    return true;
}
//----------------------------------------------------------------------
bool ScreenHeader::OutCSource( std::ofstream& out )
{
    if( false == out_c_source_disp_header(out) )
    {
	return false;
    }
    if( false == out_c_source_objects(out) )
    {
	return false;
    }
    if( false == out_c_source_bgs(out) )
    {
	return false;
    }
    return true;
}
//----------------------------------------------------------------------
__MAGBX__END
//----------------------------------------------------------------------

//
//
