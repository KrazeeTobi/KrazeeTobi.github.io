
// media_server .
var is_web_server = false;
var MEDIA_SERVER_BASEPATH = 'rtmp://nvd.nintendo.co.jp/nvd/mp4:wiiu/aurj';
var WEB_SERVER_BASEPATH = '../_movie';


var basepathstr = MEDIA_SERVER_BASEPATH;
if(is_web_server)
	basepathstr = WEB_SERVER_BASEPATH;


//

function is_alpha(){
	if($.browser.msie && $.browser.version <= 8)
		return false;
	else
		return true;
}


var volumecookie_volume = 60;

function check_volumecookie()
{
	var cval = $.cookie('volumecookie');
	if(cval)
	{
		var vals = cval.split(',');
		volumecookie_volume = vals[0];
	}
	set_volumecookie(volumecookie_volume);
	return volumecookie_volume;
}

function set_volumecookie(volume)
{
	var date=new Date();
	date.setTime(date.getTime()+(24 *60*60*1000));
	
	$.cookie('volumecookie', volume, {expires: 1, path:'/'});
}

function getSmartPhoneType()
{
	var ua = navigator.userAgent;
	var type = '';
	
	if(0 <= ua.indexOf("Android"))
	{
		type += 'android';
		if(ua.indexOf("mobile") == -1)
			type += 'tablet';
	}
	else if( (ua.indexOf("AppleWebKit") > -1 && ua.indexOf("Mobile") > -1))
	{
			type += 'iPhone';
			if(0 <= ua.indexOf("iPad"))
				type = 'iPad';
	}
	else
		type += 'pc';
	
	return type;
}

function getNintendoType()
{
	var ua = navigator.userAgent;
	var type = "";
	
	if(ua.indexOf("Nintendo WiiU") > -1)
		type = "wiiu";
	else if(ua.indexOf("Nintendo Wii") > -1)
		type = "wii";
	else if(ua.indexOf("New Nintendo 3DS") > -1)
		type = "";
	else if(ua.indexOf("Nintendo DSi") > -1)
		type = "dsi";
	else if(ua.indexOf("Nintendo 3DS") > -1)
		type = "3ds";
	
	return type;
}


function is_flashopen(){
	if (window.isGecko || window.ActiveXObject)
		return true;
	else
		return false;
}


function is_chrome(){
	var userAgent = window.navigator.userAgent.toLowerCase();
	if (userAgent.indexOf('chrome') != -1)
 		return true;
 	else
 		return false;
}

function is_ie(){
	var userAgent = window.navigator.userAgent.toLowerCase();
	if (userAgent.indexOf('msie') != -1)
 		return true;
 	else
 		return false;
}


// init .
var navcompany_flg = true;
var animenabled_flg = true;
var ie_Interchangeable_flg = false;
if(getNintendoType() != '' || getSmartPhoneType() != 'pc')
	animenabled_flg = false;

var lowievar = '';
var inituseragent = window.navigator.userAgent.toLowerCase();
var initappversion = window.navigator.appVersion.toLowerCase();
if (inituseragent.indexOf("msie") != -1)
{
	
	if(initappversion.indexOf("msie 6.") != -1)
	{
		animenabled_flg = false;
		lowievar = '6';
	}
	else if(initappversion.indexOf("msie 7.") != -1)
	{
		animenabled_flg = false;
		lowievar = '7';
	}
	
	/*
	if($.browser.msie && $.browser.version == 6)
	{
		animenabled_flg = false;
		lowievar = '6';
	}
	else if($.browser.msie && $.browser.version == 7)
	{
		animenabled_flg = false;
		lowievar = '7';
	}
	*/
	
	
	if (inituseragent.indexOf('trident') != -1 && document.documentMode && document.documentMode >= 8){
		animenabled_flg = true;
		ie_Interchangeable_flg = true;
	}
	
	
	
}

function fade_amin(obj, flg, noneflg){
	if(lowievar != '6')
	{
		var prop = {opacity: 0};
		if(flg)
			prop.opacity = 1;
		
		if(is_alpha())
		{
			if(flg && noneflg)
				obj.css('display', 'block');
			
			obj.stop(true).animate(
				prop,
				{
					duration : 500,
					easing   : 'linear',
					complete : function(){
						if(!flg && noneflg)
						{
							obj.css('display', 'none');
						}
					}
				});
		}
		else
		{
			if(noneflg)
			{
				if(flg)
					prop.display = 'block';
				else
					prop.display = 'none';
			}
			obj.css(prop);
		}
	}
	else
	{
		var prop = {'visibility': 'hidden'};
		if(flg)
			prop.visibility = 'visible';
		obj.css(prop);
	}
};

if(getNintendoType() == '' || getNintendoType() == 'wiiu')
	document.write('<style type="text/css">.txt-java{display:none;}</style>');
$(function(){
	
	var ntype = getNintendoType();
	if(ntype == '' || ntype == 'wiiu')
		$('#Container').css('background-image', 'url(../images/bacground.gif) repeat');
	
	// css .
	$('link.ncss').each(function(){
		var type = getNintendoType();
		var reg = new RegExp("("+type+"$|"+type+"_)");
		if(type != '' && $(this).attr('title').match(reg)){
			this.disabled = false;
		}else{
			this.disabled = true;
		}
	});
	
	
	// scroll end footer view .
	if(animenabled_flg)
	{
		var navcompany_show_flg = false;
		if(0 < $('.nav-company').size())
		{
			if(navcompany_flg)
			{
				var nav_company = $('.nav-company');
				var nav_company_h = '74px';
				nav_company.css('height', '0px');
				var duration_val = 400;
				
				$(window).scroll(function(){
					
					if($(window).scrollTop() + $(window).height() == $(document).height())
					{
						navcompany_show_flg = true;
						nav_company.stop(true).animate(
						{height: nav_company_h},
						{
							duration : duration_val,
							easing   : 'easeOutCubic'
						});
					}
					else if(navcompany_show_flg)
					{
						navcompany_show_flg = false;
						nav_company.stop(true).animate(
						{height: '0px'},
						{
							duration : duration_val,
							easing   : 'easeInCubic'
						});
					}
				});
			}
		}
	}
	else
	{
		if(lowievar == '')
		{
			$('#nav').css('position', 'absolute');
			$('#contents').css('position', 'relative');
		}
	}
	//scroll width.
	var fix_left = function(){
	
		$('#contents, #nav').each(function(){
			if($(this).css('position') == 'fixed')
				$(this).css('min-width', '960px').css('left', -$(window).scrollLeft());
		});
	};
	$(window).scroll(fix_left).resize(fix_left);

});
