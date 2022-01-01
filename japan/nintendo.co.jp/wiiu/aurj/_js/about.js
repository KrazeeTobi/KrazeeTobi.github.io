
function sochiopen(){
	
	var ntype = getNintendoType();
	if(lowievar != ''|| ntype != '')
	{
		if(ntype != '' && ntype != 'wiiu'){
			document.location = './sochi.html';
		}	
		else
		{
			$('.iframe5').click();
		}
	}
	else
		$('.iframe5').click();
	
	return false;
}

// init .
//document.write('<style type="text/css">[pos], .slide_box, .nav-ala, .about06{visibility:hidden;}</style>');
if(-1 == getNintendoType().indexOf('ds'))
	document.write('<style type="text/css">.simg, .spng, .sjpg{visibility:hidden;}</style>');
if(typeof init_flag == 'undefined')
$(function(){
	
	if(-1 == getNintendoType().indexOf('ds'))
	{
		$('.simg').each(function(){
			$(this).attr('src', $(this).attr('src').replace(/_s\.jpg$/, '.png'));
		});
		$('.spng').each(function(){
			$(this).attr('src', $(this).attr('src').replace(/_s\.png$/, '.png'));
		});
		$('.sjpg').each(function(){
			$(this).attr('src', $(this).attr('src').replace(/_s\.jpg$/, '.jpg'));
		});
	}
	
	
	// ga .
	var gapaths = [];
	gapaths.push('/wiiu/aurj/js/about/alacarte-wiiu/index.html');
	gapaths.push('/wiiu/aurj/js/about/alacarte-interview/index.html');
	gapaths.push('/wiiu/aurj/js/about/alacarte-mii/index.html');
	gapaths.push('/wiiu/aurj/js/about/alacarte-bestline/index.html');
	gapaths.push('/wiiu/aurj/js/about/alacarte-winter/index.html');
	
	
	var slidebox = $('.slide_box');
	var items = $('.slide_item', slidebox);
	$('.side-next').css('display', 'block');
	$('.side-prev').css('display', 'block');
	var btn_next = $('.btn-slidenext');
	var btn_prev = $('.btn-slideprev');
	var now_pos = 0;
	var max_pos = items.size() - 1;
	var min_pos = 0;
	var slide_val = items.eq(0).outerWidth();
	var duration_val = 450;
	btn_prev.css('opacity', 0);
	var indexs = $('.navbtn');
	$('.slide-ala').css('width', '800px');
	
	
	var slideboxanim = function(){
		
		if(-1 == getNintendoType().indexOf('ds'))
		{
			indexs.each(function(){
				var obj = $(this).find('img');
				obj.attr('src', obj.attr('src').replace(/_o.(jpg|png|gif)$/, '.$1'));
			});
			indexs.eq(now_pos).find('img').attr('src', indexs.eq(now_pos).find('img').attr('src').replace(/.(jpg|png|gif)$/, '_o.$1'));
		}
		
		slidebox.stop(true).animate(
			{left: slide_val * now_pos * (-1)},
			{
				duration : duration_val,
				easing   : 'easeOutCubic',
				step     : function(step){},
				complete : function(){
					
					// ga .
					_gaq.push(['_trackPageview',gapaths[now_pos]]);
				}
			});
	};
	
	btn_next.click(function(){
		if(now_pos == max_pos)
			return false;
		
		now_pos += 1;
		if(now_pos < max_pos)
			fade_amin(btn_next, true, true);
		else
			fade_amin(btn_next, false, true);
			
		fade_amin(btn_prev, true, true);
		
		if(now_pos == min_pos)
			fade_amin(btn_prev, false, true);
		
		slideboxanim();
		return false;
	});
	
	btn_prev.click(function(){
		if(now_pos == min_pos)
			return false;
		
		now_pos -= 1;
		if(min_pos < now_pos)
			fade_amin(btn_prev, true, true);
		else
			fade_amin(btn_prev, false, true);
		fade_amin(btn_next, true, true);
		
		slideboxanim();
		return false;
	});
	
	indexs.click(function(){
		now_pos = indexs.index(this) - 1;
		btn_next.click();
		return false;
	});
	
	
	if(-1 == getNintendoType().indexOf('ds'))
	{
		indexs.eq(0).click();
		indexs.hover(
			function(){
				
				if(indexs.index($(this)) != now_pos)
				{
					var obj = $(this).find('img');
					obj.attr('src', obj.attr('src').replace(/.(jpg|png|gif)$/, '_o.$1'));
				}
			}, function(){
				if(indexs.index($(this)) != now_pos)
				{
					var obj = $(this).find('img');
					obj.attr('src', obj.attr('src').replace(/_o.(jpg|png|gif)$/, '.$1'));
				}
		});
	}
	
	
	if(-1 == getNintendoType().indexOf('ds'))
	{
		$('.simg').each(function(){
			$(this).attr('src', $(this).attr('src').replace(/_s\.jpg$/, '.png'));
		});
		$('.spng').each(function(){
			$(this).attr('src', $(this).attr('src').replace(/_s\.png$/, '.png'));
		});
		$('.sjpg').each(function(){
			$(this).attr('src', $(this).attr('src').replace(/_s\.jpg$/, '.jpg'));
		});
		
			setTimeout(function(){
				//$('[pos], .slide_box, .nav-ala, .about06').css('visibility', 'visible');
				$('.simg, .spng, .sjpg').css('visibility', 'visible');
				if(lowievar == '6')
					DD_belatedPNG.fix('img, .png-bg');
							
							
				if(animenabled_flg)
				{
					var tv_scrolled_top = $('.about06').offset().top;
					var tv_scrolled = function(){
						var sb = $(window).scrollTop() + $(window).height() * 0.8;
						var obj = $('.about06');
						if(obj[0].animated)
							return;
						obj.css('visibility', 'visible');
						var top = tv_scrolled_top;
						if(top < sb)
						{
							obj[0].animated = true;
							var dls = $('dl', obj);
							var delay = 500;
							dls.each(function(){
								var imgs = $('img', this);
								var w = $(imgs[0]).attr('width');
								var h = $(imgs[0]).attr('height');
								$(imgs[0]).css({'position':'relative', 'visibility':'visible'}).css({'width':0, 'height':0, 'top':(w / 2), 'left':(h  / 2)}).delay(delay).animate({'width':w, 'height':h, 'top':0, 'left':0}, {'duration': 600, 'easing':'easeOutBack', 'complete':function(){
									$(imgs[1]).css({'visibility':'visible', 'opacity':0}).animate({'opacity':1}, {'duration':300});
									$(imgs[2]).css({'visibility':'visible', 'opacity':0}).animate({'opacity':1}, {'duration':300});
								}});
								$(imgs[1]).css('visibility', 'hidden');
								$(imgs[2]).css('visibility', 'hidden');
								delay += 200;
							});
						}
					};
					$(window).scroll(tv_scrolled);
					$('.about06 dl img').css('visibility', 'hidden');
					tv_scrolled();
					
					
					var win_obj = $(window);
					var bgs = $('.about-bg02, .about-bg03, .about-bg04');
					var bgboxs = [];
					bgs.each(function(){
						var bgbox = {};
						bgbox.obj = $(this);
				//		bgbox.obj.css('position', 'fixed');
						bgbox.height = $(this).height();
						bgbox.top = $(this).offset().top;
						bgboxs.push(bgbox);
				//		bgbox.csstop = parseInt($(this).css('top').replace('px', ''));
					});
					
					$('#contents').css('width', '100%').parent().css('height', $('#contents').height());

					
					var timerid = null;
					var old_st = 0;
					var old_time = (new Date()) * 1;
					var stout = function() {
						var st = win_obj.scrollTop();
						if(timerid)
						{
							clearTimeout(timerid);
							timerid = null;
						}
						if(old_time == null)
							old_time = (new Date()) * 1;
						var now_time = (new Date()) * 1;
						
						var dst = st - old_st;
						var dtime = now_time - old_time;
						if(dtime < 0)
							dtime = 0;
						else if(1000 < dtime)
							dtime = 1000;
						var next_st = dst * dtime / 1000 * 2 + old_st;
						if(-1 < dst && dst < 1)
							next_st = st;
						
						$('#contents').css('position', 'fixed').css('top', -next_st);
						$('.inline').css('position', 'relative');
						
						old_time = now_time;
						if(st != next_st)
						{
							timerid = setTimeout(function(){
								stout(st);
							}, 1);
						}
						else
							old_time = null;
						old_st = next_st;
						parallax(old_st);
						//parallax(st);
					} ;
					
					var parallax = function(st){
						var sm = st + win_obj.height() * 0.5;
						for(var ii=0; ii < bgboxs.length; ii++)
						{
							var bgbox = bgboxs[ii];
							var mid = bgbox.top + bgbox.height * 0.5;
							var bgimg = $('img', bgbox.obj);
							var bgimgheight = bgimg.attr('height');
							var per = (mid - sm) / bgimgheight;
							var dtop = -per * bgimgheight * 0.5 * bgimgheight / win_obj.height() / 2;
							
							bgimg.css('margin-top', -bgimgheight / 2 + dtop);
						}
					};
					
					stout();
					win_obj.scroll(stout);
					win_obj.resize(stout);
					
					var aboutscroll = function(){
						var items = $('.ttlimg, .txtimg, .btnimg,.img-aboutcap01, .img-aboutcap02, .img-about03');
						var sb = win_obj.scrollTop() + win_obj.height() * 0.9;
						var delay = 0;
						items.each(function() {
							var obj = $(this);
							if(obj[0].animated)
								return;
							else
								obj.css('opacity', 0);
							
							var top = obj.offset().top + obj.height();
							delay = 0;
							if(top < sb)
							{
								
								obj[0].animated = true;
								var animprop = {left: obj.css('left'), top: obj.css('top')};
								var startprop = {opacity: 0};
								
								if(obj.attr('pos') == 'l')
									startprop.left = '-=50px';
								else if(obj.attr('pos') == 'r')
									startprop.left = '+=50px';
								else if(obj.attr('pos') == 'b')
									startprop.top = '+=50px';
								obj.css(startprop);
								
								if(is_alpha())
									animprop.opacity = 1;
								else
									obj.css('opacity', 1);
								
								setTimeout(function(){
									obj.stop(true).animate(animprop, {'duration': 300, 'easing':'easeOutQuart'});
								}, delay);
								delay += 100;
								
							}
							
						});
					};
					win_obj.scroll(aboutscroll);
					setTimeout(function(){
						aboutscroll();
					}, 500);
					
					
					if(is_chrome() || is_ie())
					{
						$(document).mousewheel(function(eo, delta, deltaX, deltaY){
							var scrollnotch = 100 * deltaY * -1;
							win_obj.scrollTop(win_obj.scrollTop() + scrollnotch);
							return false;
						});
					}
					
					
					
				}
			}, 1000);
			
	}
	
	
	// flash .
	var ntype = getNintendoType();
	if(ntype != 'wii' && ntype != 'dsi' && ntype != '3ds' && !getSmartPhoneType().match(/android/))
	{
		var flashvars = {};
		// var flashVars = {moviepath: basepathstr + '/pchigh/'};
		var params = { wmode:"transparent", quality:"high", scale:"noscale", salign:"mc"};
		var attributes = {};
		swfobject.embedSWF("../_swf/about.swf", "about01", "100%", "696", "9.0.115", "", flashvars, params, attributes);
		
		
		var flashvars2 = {'page':'about'};
		var params2 = { wmode:"transparent", quality:"high"};
		var attributes2 = {};
		swfobject.embedSWF("../_swf/menu.swf", "flashcontent", "940", "200", "9.0.115", "", flashvars2, params2, attributes2);
	}
	
	
	if(lowievar != ''|| ntype != '')
	{
		if(ntype != '' && ntype != 'wiiu')
		{
			$(".iframe1").click(function(){
				document.location = '../mode/online1.html';
				$.cookie('bkhref', document.location.href, {expires: 0, path: '/' });
				return false;
			});
			$(".iframe4").click(function(){
				document.location = './miiverse.html';
				return false;
			});
		}
		else
		{
			setTimeout(function(){
				$(".iframe1").colorbox({iframe:true, width:"850px", height:"625px", 'onComplete':function(){
					setTimeout(function(){
						$('.cboxIframe').contents().find('#Container').css('width', '+=1');
						setTimeout(function(){$('.cboxIframe').contents().find('#Container').css('width', '-=1');}, 100);
					}, 100);
				}});
				$(".iframe3").colorbox({iframe:true, width:"850px", height:"55%"});
				$(".iframe4").colorbox({iframe:true, width:"850px", height:"500px", 'onComplete':function(){
					setTimeout(function(){
						$('.cboxIframe').contents().find('#Container').css('width', '+=1');
						setTimeout(function(){$('.cboxIframe').contents().find('#Container').css('width', '-=1');}, 100);
					}, 100);
				}});
				$(".iframe5").colorbox({iframe:true, width:"851px", height:"450px", 'onComplete':function(){
					setTimeout(function(){
						$('.cboxIframe').contents().find('#Container').css('width', '+=1');
						setTimeout(function(){$('.cboxIframe').contents().find('#Container').css('width', '-=1');}, 100);
					}, 100);
				}});
			}, 1);
		}
	}
	else
	{
		setTimeout(function(){
			$(".iframe1").attr('href', $(".iframe1").attr('href').replace('online_a1.html', 'online1.html'));
			$(".iframe1").colorbox({iframe:true, width:"850px", height:"625px"});
			$(".iframe3").colorbox({iframe:true, width:"850px", height:"55%"});
			$(".iframe4").colorbox({iframe:true, width:"850px", height:"500px"});
			$(".iframe5").colorbox({iframe:true, width:"851px", height:"450px"});
		}, 1);
	}
	
	
});

init_flag = true;



