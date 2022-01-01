//2013.11.20ADD
$(function()
{
$('#contents').bind("contextmenu",function(e)
{
return false;
});
});


function opennetwork(){
	
	var ntype = getNintendoType();
	if(lowievar != ''|| getNintendoType() != '')
	{
		if(ntype == 'wii' || ntype == '3ds' || ntype == 'dsi')
			document.location = './mode/online_i1.html';
		else
			$('.iframe1').click();
	}
	else
		$('.iframe1').click();
	
	return false;
	
}


var navcompany_flg = false;

$(function(){
	
	if(0 <= getNintendoType().indexOf('ds'))
	{
		$('.simg').each(function(){
			$(this).attr('src', $(this).attr('src').replace(/\.(jpg|png)$/, '_s.jpg'));
		});
		$('.spng').each(function(){
			$(this).attr('src', $(this).attr('src').replace(/\.png$/, '_s.png'));
		});
	}
	
	setTimeout(function(){
		if(0 < $('object, embed').size())
		{
			var resized = function(){
				
				
				var win_height = $(window).height();
				if(win_height < 595)
					win_height = 595;
				$('#main, #flashArea').css('height', win_height);
				$('#container').css('height', win_height + 74);
			};
			resized();
			$(window).resize(resized);
		}
	}, 1);
	
	
	
	if(getNintendoType() != 'wii' && !getSmartPhoneType().match(/android/))
	{
		var flashVars = {moviepath: basepathstr + '/pchigh/'};
		var parms = {
			wmode:"opaque", Menu:"false", quality:"high", scale:"noscale", salign:"mc"
			};
		var attributes = {};
		swfobject.embedSWF("_swf/top.swf", "flash", "100%", "100%", "9.0.115", "", flashVars, parms, attributes);
	}
	setTimeout(function(){
		if($('object, embed').size() == 0)
		{
			if(getNintendoType() == '' && getSmartPhoneType() == 'pc')
			{
				$('#flashArea').css({'background-image':'url(./common/images/index/bg_main.jpg)'});
				$('#flashArea img').css({'visibility':'visible'});
			}
			else
				$('#flashArea img').css({'visibility':'visible'});
		}
	}, 750);

	
	var ntype = getNintendoType();
	if(lowievar != ''|| ntype != '')
	{
		if(ntype != ''&& ntype != 'wiiu')
		{
			$(".iframe1").click(function(){
				document.location = './mode/online1.html';
				$.cookie('bkhref', document.location.href, {expires: 0, path: '/' });
				return false;
			});
		}
		else
		{
			setTimeout(function(){
				$(".iframe1").colorbox({iframe:true, width:"850px", height:"625px"});
			}, 1);
		}
	}
	else
	{
		$(".iframe1").attr('href', $(".iframe1").attr('href').replace('online_i1.html', 'online.html'));
		setTimeout(function(){
			$(".iframe1").colorbox({iframe:true, width:"850px", height:"625px"});
		}, 1);
	}
	
});


