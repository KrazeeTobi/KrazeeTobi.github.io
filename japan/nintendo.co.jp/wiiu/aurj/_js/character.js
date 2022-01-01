
// init .
if(-1 == getNintendoType().indexOf('ds'))
	document.write('<style type="text/css">.simg, [lr], .spng, .chara-list, .btn-next{visibility:hidden;}</style>');
$(function(){
	
	
	
	/*
	if(0 <= getNintendoType().indexOf('ds'))
	{
		$('.simg').each(function(){
			$(this).attr('src', $(this).attr('src').replace(/\.(jpg|png)$/, '_s.jpg'));
		});
		$('.spng').each(function(){
			$(this).attr('src', $(this).attr('src').replace(/\.png$/, '_s.png'));
		});
	}
	*/
	
	var win_obj = $(window);
	
	if(-1 == getNintendoType().indexOf('ds'))
	{
		//$('.simg, .spng, [lr]').css('visibility', 'hidden');
		//$('.chara-list, .btn-next').css('visibility', 'hidden');
		$('.simg').each(function(){
			$(this).attr('src', $(this).attr('src').replace(/_s\.jpg$/, '.png'));
		});
		$('.spng').each(function(){
			$(this).attr('src', $(this).attr('src').replace(/_s\.png$/, '.png'));
		});
		
		setTimeout(function(){
			$('.simg, [lr], .spng, .chara-list, .btn-next').css('visibility', 'visible');
			if(lowievar == '6'){
				DD_belatedPNG.fix('img, .png-bg');
			}
			
			
			
			
			if(animenabled_flg)
			{
				var player_selector_show = function(visibility)
				{
					if(visibility)
						$('.btn-ttl').stop(true).animate({'top':0}, {'duration':500, 'easing':'easeOutQuad'});
					else
						$('.btn-ttl').stop(true).animate({'top':-$('.btn-ttl').height()}, {'duration':500, 'easing':'easeOutQuad'});
				};
				$('.btn-ttl').css('display', 'block');
				var mouse_y = 200;
				var scroll_y = 0;
				var player_box = $('.chara-list');
				player_box.css({'position': 'fixed'});
				$('ul', player_box).css('opacity', 0).delay(1000).animate({'opacity': 1}, {'duration':1000});
				var playerselector_old_state = -1;
				var playerselector = function(){
					
					var box_height = player_box.height();
					if(mouse_y < box_height)
					{
						if(playerselector_old_state != 2)
						{
							player_box.stop(true);
							if(player_box.css('position') == 'absolute')
								player_box.css('top', -scroll_y);
							
							player_box.css('position', 'fixed');
							player_box.animate({'top': 0}, {duration : 300, easing   : 'easeOutQuint'});
							player_selector_show(false);
						}
						playerselector_old_state = 2;
					}
					else
					{
						if(scroll_y < box_height)
						{
							if(playerselector_old_state != 0)
							{
								player_box.stop(true);
								player_box.css('position', 'absolute');
								player_box.css('top', 0);
								player_selector_show(false);
							}
							playerselector_old_state = 0;
						}
						else
						{
							if(playerselector_old_state != 1)
							{
								if(player_box.css('position') == 'absolute')
									player_box.css('top', -box_height);
							
								player_box.stop(true);
								player_box.css('position', 'fixed');
								player_box.animate({'top': -box_height}, {duration : 100, easing   : 'easeOutQuint'});
								player_selector_show(true);
							}
							playerselector_old_state = 1;
						}
					}
				};
				playerselector();
				
				/*
				$(window).scroll(function(){
					scroll_y = $(window).scrollTop();
					playerselector();
				});
				*/
				
				$('body').mousemove(function(evt){
					mouse_y = evt.clientY;
					playerselector();
				});
				
				var scroll_characters = {};
				$('a', player_box).each(function(){
					var ahref = $(this).attr('href');
					if(ahref.indexOf('#') == 0)
					{
						try{
							scroll_characters[ahref] = $(ahref).offset().top;
							$(this).click(function(){
								$('html, body').stop(true).animate({'scrollTop':scroll_characters[ahref] - 160}, {'duration':300, 'easing':'easeOutQuart'});
								document.location.hash = ahref;
								return false;
							});
						}catch(e){}
					}
					
					
				});
				
				var scroll_check_margin = 170;
				$('.btn-next a').click(function(){
					var st = $(window).scrollTop();
					var flag = false;
					for (var ahref in scroll_characters)
					{
						if(st < scroll_characters[ahref] - scroll_check_margin)
						{
							$('html, body').stop(true).animate({'scrollTop':scroll_characters[ahref]}, {'duration':300, 'easing':'easeOutQuart'});
							document.location.hash = ahref;
							break;
						}
					}
					return false;
				});
				var last_chara_box = $('.chara-box:last');
				var last_chara_box_top = last_chara_box.offset().top;
				$('.btn-next a').css('opacity', 0).delay(3000).animate({'opacity': '1'}, {'duration': 500});
				var next_button_old_status = -1;
				$(window).scroll(function(){
					var st = $(window).scrollTop();
					if(st < last_chara_box_top - scroll_check_margin && st + $(window).height() < $(document).height()  - scroll_check_margin)
					{
						if(next_button_old_status != 0)
						{
							$('.btn-next a').css('display', 'inline');
							$('.btn-next a').stop(true).animate({'opacity': '1'}, {'duration': 500});
						}
						next_button_old_status = 0;
					}
					else
					{
						if(next_button_old_status != 1)
						{
							$('.btn-next a').stop(true).animate({'opacity': '0'}, {'duration': 500, 'complete':function(){
								$(this).css('display', 'none');
							}});
						}
						next_button_old_status = 1;
					}
					
				});
				
				
				$('.chara-img, .chara-innner [lr]').css('opacity', 0);
				var chara_objs = {};
				var chara_props = {};
				
				// charatitle .
				var charattl_offset = 800;
				var charattl_anim = function(chara_name, delay){
					var obj = $('.title-'+chara_name);
					var img_obj = obj.find('[lr]');
					var def_prop = {left: obj.css('left')};
					
					if(img_obj.attr('lr') == 'l')
						obj.css('left' , '-='+charattl_offset);
					else
						obj.css('left' , '+='+charattl_offset);
					
					setTimeout(function(){
						if(is_alpha())
							def_prop.opacity = 1;
						else
							obj.css('opacity', 1);
						img_obj.css('opacity', 1);
						obj.animate(
							def_prop,
							{
								duration : 300,
								easing   : 'easeOutQuint'
							});
					}, delay);
				};
				
				// charatxt .
				var charatxt_offset = 800;
				var charatxt_anim = function(chara_name, delay){
					var obj = $('.txt-'+chara_name);
					var img_obj = obj.find('[lr]');
					var def_prop = {
						left: obj.css('left')};
					
					if(img_obj.attr('lr') == 'l')
						obj.css('left' , '-='+charatxt_offset);
					else
						obj.css('left' , '+='+charatxt_offset);
					
					setTimeout(function(){
						img_obj.css('opacity', 1);
						obj.animate(
							def_prop,
							{
								duration : 300,
								easing   : 'easeOutQuint',
								complete: function(){
									var nameobj = $('.txt-name'+chara_name);
									var leftval = '-=150px';
									if(nameobj.attr('lr') == 'r')
										leftval = '+=150px';
									
									var nameprop = {left: nameobj.css('left')};
									nameobj.css('left', leftval);
									if(is_alpha())
										nameprop.opacity = 1;
									else
										nameobj.css('opacity', 1);
									
									nameobj.animate(nameprop, {duration : 300, easing   : 'easeOutQuint'});
								}
							});
					}, delay);
				};
				
				// charaimg .
				var chara_anim = function(chara_obj, chara_prop){
					var prop = {};
					prop.left   = chara_obj.css('left');
					prop.top    = chara_obj.css('top');
					prop.width  = chara_obj.attr('width');
					prop.height = chara_obj.attr('height');
					chara_obj.css({
							left: prop.width / 2 + chara_prop.start_left,
							top: prop.height / 2 + chara_prop.start_top,
							width: '0px',
							height: '0px'});
					
					setTimeout(function(){
						if(is_alpha())
							prop.opacity = 1;
						else
							chara_obj.css('opacity', 1);
						
						chara_obj.stop(true).animate(
								prop,
								{
									duration : chara_prop.duration,
									easing   : chara_prop.easing,
									complete : function(){
										var names = chara_obj.attr('cname').split('-');
										var cnt = names.length;
										for(var ii=0; ii < cnt; ii++)
										{
											charattl_anim(names[ii], 100 * (ii + 1));
											charatxt_anim(names[ii], 200 * (ii + 1));
										}
									}
								});
					}, 1);
				}
				
				$('.chara-name').css('opacity', 0);
				
				chara_objs['mario'] = $('.mario .chara-img');
				chara_objs['mario'].offsettop = $('.mario .chara-img').offset().top;
				chara_props['mario'] = {
					start_left: 900,
					start_top : -900,
					duration  : 750,
					easing    : 'easeOutCubic'};
				
				chara_objs['sonic'] = $('.sonic .chara-img');
				chara_objs['sonic'].offsettop = $('.sonic .chara-img').offset().top;
				chara_props['sonic'] = {
					start_left: 900,
					start_top : 650,
					duration  : 950,
					easing    : 'easeInCubic'};
				
				chara_objs['amy_peach'] = $('.amy-peach .chara-img');
				chara_objs['amy_peach'].offsettop = $('.amy-peach .chara-img').offset().top;
				chara_props['amy_peach'] = {
					start_left: 150,
					start_top : -200,
					duration  : 950,
					easing    : 'easeOutCubic'};
				
				chara_objs['group01'] = $('.group01 .chara-img');
				chara_objs['group01'].offsettop = $('.group01 .chara-img').offset().top;
				chara_props['group01'] = {
					start_left: 0,
					start_top : 0,
					duration  : 800,
					easing    : 'easeOutCubic'};
					
				chara_objs['vector'] = $('.vector .chara-img');
				chara_objs['vector'].offsettop = $('.vector .chara-img').offset().top;
				chara_props['vector'] = {
					start_left: -1000,
					start_top : 0,
					duration  : 750,
					easing    : 'easeInCubic'};
					
				chara_objs['wario'] = $('.wario .chara-img');
				chara_objs['wario'].offsettop = $('.wario .chara-img').offset().top;
				chara_props['wario'] = {
					start_left: 1000,
					start_top : 0,
					duration  : 750,
					easing    : 'easeInCubic'};
					
				chara_objs['knucles_yoshi'] = $('.knucles-yoshi .chara-img');
				chara_objs['knucles_yoshi'].offsettop = $('.knucles-yoshi .chara-img').offset().top;
				chara_props['knucles_yoshi'] = {
					start_left: -1000,
					start_top : 450,
					duration  : 750,
					easing    : 'easeOutCubic'};
					
				chara_objs['daisy'] = $('.daisy .chara-img');
				chara_objs['daisy'].offsettop = $('.daisy .chara-img').offset().top;
				chara_props['daisy'] = {
					start_left: -1500,
					start_top : -900,
					duration  : 900,
					easing    : 'easeOutCubic'};
					
				chara_objs['blaze'] = $('.blaze .chara-img');
				chara_objs['blaze'].offsettop = $('.blaze .chara-img').offset().top;
				chara_props['blaze'] = {
					start_left: 0,
					start_top : 600,
					duration  : 1000,
					easing    : 'easeInCubic'};
					
				chara_objs['shadow_donkey'] = $('.shadow-donkey .chara-img');
				chara_objs['shadow_donkey'].offsettop = $('.shadow-donkey .chara-img').offset().top;
				chara_props['shadow_donkey'] = {
					start_left: 0,
					start_top : 100,
					duration  : 750,
					easing    : 'easeInQuart'};
				
				chara_objs['group02'] = $('.group02 .chara-img');
				chara_objs['group02'].offsettop = $('.group02 .chara-img').offset().top;
				chara_props['group02'] = {
					start_left: 900,
					start_top : -400,
					duration  : 750,
					easing    : 'easeInQuart'};
				
				
				var show_flgs = {
					mario: true,
					sonic: true,
					amy_peach: true,
					group01: true,
					vector: true,
					wario: true,
					knucles_yoshi: true,
					daisy: true,
					blaze: true,
					shadow_donkey: true,
					group02: true};
				
				
				setTimeout(function(){
					if(show_flgs.mario){
						show_flgs.mario = false;
						chara_anim(chara_objs['mario'], chara_props['mario']);
					}
					if(show_flgs.sonic){
						show_flgs.sonic = false;
						chara_anim(chara_objs['sonic'], chara_props['sonic']);
					}
				}, 800);
					
//				var win_obj = $(window);
				var winh = win_obj.height();
				win_obj.resize(function(){
					winh = win_obj.height();
				});
				
				var charascroll = function(st){
					
					var dtop = winh + st;
					if(show_flgs.mario && dtop - chara_objs['mario'].offsettop >= 0){
						show_flgs.mario = false;
						chara_anim(chara_objs['mario'], chara_props['mario']);
					}
					if(show_flgs.sonic && dtop - chara_objs['sonic'].offsettop >= 0){
						show_flgs.sonic = false;
						chara_anim(chara_objs['sonic'], chara_props['sonic']);
					}
					if(show_flgs.amy_peach && dtop - chara_objs['amy_peach'].offsettop >= 230){
						show_flgs.amy_peach = false;
						chara_anim(chara_objs['amy_peach'], chara_props['amy_peach']);
					}
					if(show_flgs.group01 && dtop - chara_objs['group01'].offsettop >= 230){
						show_flgs.group01 = false;
						chara_anim(chara_objs['group01'], chara_props['group01']);
					}
					if(show_flgs.vector && dtop - chara_objs['vector'].offsettop >= 80){
						show_flgs.vector = false;
						chara_anim(chara_objs['vector'], chara_props['vector']);
					}
					if(show_flgs.wario && dtop - chara_objs['wario'].offsettop >= -20){
						show_flgs.wario = false;
						chara_anim(chara_objs['wario'], chara_props['wario']);
					}
					if(show_flgs.knucles_yoshi && dtop - chara_objs['knucles_yoshi'].offsettop >= 230){
						show_flgs.knucles_yoshi = false;
						chara_anim(chara_objs['knucles_yoshi'], chara_props['knucles_yoshi']);
					}
					if(show_flgs.daisy && dtop - chara_objs['daisy'].offsettop >= 50){
						show_flgs.daisy = false;
						chara_anim(chara_objs['daisy'], chara_props['daisy']);
					}
					if(show_flgs.blaze && dtop - chara_objs['blaze'].offsettop >= 0){
						show_flgs.blaze = false;
						chara_anim(chara_objs['blaze'], chara_props['blaze']);
					}
					if(show_flgs.shadow_donkey && dtop - chara_objs['shadow_donkey'].offsettop >= 10){
						show_flgs.shadow_donkey = false;
						chara_anim(chara_objs['shadow_donkey'], chara_props['shadow_donkey']);
					}
					if(show_flgs.group02 && dtop - chara_objs['group02'].offsettop >= 230){
						show_flgs.group02 = false;
						chara_anim(chara_objs['group02'], chara_props['group02']);
					}
				}
				win_obj.scroll(charascroll);
				
				
				var bgs = $('.bg-box');
				var bgboxs = [];
				bgs.each(function(){
					var bgbox = {};
					bgbox.obj = $(this);
					bgbox.height = $(this).height();
					bgbox.top = $(this).offset().top;
					
					bgboxs.push(bgbox);
				});
				
				$('#contents').css('width', '100%').parent().css('height', $('#contents').height());
				
				var scrollspeed = 15;
				var inituseragent = window.navigator.userAgent.toLowerCase();
				var initappversion = window.navigator.appVersion.toLowerCase();
				if (inituseragent.indexOf("msie") != -1)
				{
					//if(initappversion.indexOf("msie 8.") != -1)
					if($.browser.msie && $.browser.version == 8 || ie_Interchangeable_flg)
					{
						scrollspeed = 3.5;
					}
				}
				
				
				var timerid = null;
				var old_st = 0;
				var old_time = (new Date()) * 1;
				var stout = function(){
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
					
					var next_st = dst * dtime / 1000 * scrollspeed + old_st;
					if(-1 < dst && dst < 1)
						next_st = st;
					
					$('#contents').css('position', 'fixed').css('top', -next_st);
					charascroll(next_st);
					/*
					for(var ii=0; ii < bgboxs.length; ii++)
					{
						var bgbox = bgboxs[ii];
						bgbox.obj.css('top', bgbox.csstop - next_st);
					}
					*/
					
					old_time = now_time;
					if(st != next_st)
					{
						timerid = setTimeout(function(){
							stout();
						}, 1);
					}
					else
						old_time = null;
					old_st = next_st;
					parallax(old_st);
					
					scroll_y = old_st;
					playerselector();
				} ;
				
				var parallax = function(st){
					var sm = st + win_obj.height() * 0.5;
					for(var ii=0; ii < bgboxs.length; ii++)
					{
						var bgbox = bgboxs[ii];
						//console.log(ii + ' : '+ bgboxs.length);
						var mid = bgbox.top + bgbox.height * 0.5;
						var bgimg = $('img', bgbox.obj);
						var bgimgheight = bgimg.attr('height');
						var per = (mid - sm) / bgimgheight;
						var dtop = -per * bgimgheight * 0.5 * bgimgheight / win_obj.height() * 0.5;
						
						
						bgimg.css('margin-top', -bgimgheight / 2 + dtop);
					}
				};
				
				stout();
				win_obj.resize(stout);
				win_obj.scroll(stout);
			}
			else
			{
				$('.btn-next').css('display', 'none');
				
				if(lowievar == '6')
				{
				/*
					$('.chara-list').css('position', 'relative');
					$('div, p').css('position', 'relative');
				*/
				//$('.bg-box').css('display', 'none');
				}
				else if(lowievar == '7')
				{
					$('.chara-list').css('position', 'relative');
				}
			}
			
			if(getNintendoType() != 'wii')
			{
				var flashvars = {'page':'character'};
				var params = { wmode:"transparent", quality:"high"};
				var attributes = {};
				swfobject.embedSWF("../_swf/menu.swf", "flashcontent", "940", "200", "9.0.115", "", flashvars, params, attributes);
			}
			
			if(is_chrome() || is_ie())
			{
				$(document).mousewheel(function(eo, delta, deltaX, deltaY){
					var scrollnotch = 100 * deltaY * -1;
					win_obj.scrollTop(win_obj.scrollTop() + scrollnotch);
					return false;
				});
			}
			
		}, 1000);
		
	}
	else
		$('.btn-next').css('display', 'none');
	
});



