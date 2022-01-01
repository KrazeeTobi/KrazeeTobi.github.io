
// init .
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
	
	if(animenabled_flg)
	{
		// charatitle .
		var charattl_offset = 150;
		var charattl_anim = function(){
			var obj = $('#visual-ttl');
			obj.css('opacity', '0');
			var def_prop = {
				left: obj.css('left')};
			
			obj.css('left', '+='+charattl_offset);
			setTimeout(function(){
				if(is_alpha())
					def_prop.opacity = 1;
				else
					obj.css('opacity', '1');
				
				obj.animate(
					def_prop,
					{
						duration : 350,
						easing   : 'easeOutSine'
					});
			}, 750);
		};
		
		// charatxt .
		var charatxt_offset = 75;
		var charatxt_anim = function(){
			var obj = $('.txt-visual');
			obj.css('opacity', '0');
			var def_prop = {
				left: obj.css('left')};
			
			obj.css('left' , '+='+charattl_offset);
			setTimeout(function(){
				if(is_alpha())
					def_prop.opacity = 1;
				else
					obj.css('opacity', '1');
				
				obj.animate(
					def_prop,
					{
						duration : 350,
						easing   : 'easeInSine'
					});
			}, 950);
		};
		
		// charaimg .
		var chara_anim = function(){
			var chara_obj = $('#title-chara');
			var prop = {};
			
			prop.left   = 0;
			//prop.top    = chara_obj.css('top');
			//prop.width  = chara_obj.attr('width');
			//prop.height = chara_obj.attr('height');
			chara_obj.css({
					position: 'relative',
					left: '-80px',
					//top: prop.height / 2 + 60,
					//width: prop.width / 2,
					//height: prop.height / 2,
					opacity: 0});
			
			setTimeout(function(){
				if(is_alpha())
					prop.opacity = 1;
				else
					chara_obj.css('opacity', 1);
				
				chara_obj.stop(true).animate(
						prop,
						{
							duration : 350,
							easing   : 'easeInSine'
						});
			}, 1250);
		}
		
		charattl_anim();
		charatxt_anim();
		chara_anim();
		
		
		// icon .
		var win_obj = $(window);
		var win_h = win_obj.height();
		var doc_h = $(document).height();
		var icons = $('.icon-img, .icon-num img');
		var icon_show_flgs = [];
		var icon_show_props = [];
		var icon_cnt = icons.size();
		var duration_val = 650;
		var border = 0.66;
		
		for(var ii=0; ii<icon_cnt; ii++)
		{
			var obj = icons.eq(ii);
			var prop = {};
			
			prop.left = obj.css('left');
			prop.top = obj.css('top');
			prop.width = obj.attr('width');
			prop.height = obj.attr('height');
			obj.css({left: prop.width / 2, top: prop.height / 2, width: '0px', height: '0px'});
			
			icon_show_props.push(prop);
			icon_show_flgs.push(false);
		}
		
		
		var ttls = $('.ttl');
		ttls.css('opacity', 0);
		var ttl_show_flgs = [];
		for(var jj=0; jj<ttls.size(); jj++)
			ttl_show_flgs.push(false);
		
		
		win_obj.resize(function(){
			win_h = win_obj.height();
		});
		
		var animcnt = 0;
		var scrolled = function(){
			
			var scroll_val = win_obj.scrollTop();
			
			for(var ii=0; ii<icon_cnt; ii++)
			{
				// icon .
				var obj = icons.eq(ii);
				var top_val = obj.offset().top;
				
				if(!icon_show_flgs[ii] && top_val - scroll_val <= win_h * border)
				{
					icon_show_flgs[ii] = true;
					var animprop = {
						left  : icon_show_props[ii].left,
						top   : icon_show_props[ii].top,
						width : icon_show_props[ii].width,
						height: icon_show_props[ii].height};
					
					if(is_alpha())
						animprop.opacity = 1;
					else
						obj.css('opacity', 1);
					
					animcnt++;
					obj.stop(true).delay(150 * animcnt).animate(
						animprop,
						{
							duration : duration_val,
							easing   : 'easeOutBounce',
							complete : function(){
								animcnt--;
							}
						});
				}
				/*
				else if(icon_show_flgs[ii] && win_h < top_val - scroll_val)
				{
					icon_show_flgs[ii] = false;
					var animprop = {
						left  : icon_show_props[ii].width / 2,
						top   : icon_show_props[ii].height / 2,
						width : '0px',
						height: '0px'};
					
					if(is_alpha())
						animprop.opacity = 0;
					else
						obj.css('opacity', 0);
					
					obj.stop(true).animate(
						animprop,
						{
							duration : duration_val,
							easing   : 'easeInCubic'
						});
				}
				*/
			}
			
			// ttl .
			for(var jj=0; jj<ttls.size(); jj++)
			{
				var ttlobj = ttls.eq(jj);
				var top_val = ttlobj.offset().top;
				
				if(!ttl_show_flgs[jj] && top_val - scroll_val <= win_h * 0.7)
				{
					ttl_show_flgs[jj] = true;
					ttlprop = {left: ttlobj.css('left')};
					if(is_alpha())
						ttlprop.opacity = 1;
					else
						ttlobj.css('opacity', 1);
					ttlobj.css('left', '+=50px');
					
					ttlobj.stop(true).animate(
						ttlprop,
						{
							duration : 250,
							easing   : 'easeInSine'
						}
					);
				}
				/*
				else if(ttl_show_flgs[jj] && win_h < top_val - scroll_val)
				{
					ttl_show_flgs[jj] = false;
					ttlprop = {left: ttlobj.css('left')};
					if(is_alpha())
						ttlprop.opacity = 0;
					else
						ttlobj.css('opacity', 0);
					ttlobj.css('left', '+=50px');
					
					ttlobj.stop(true).animate(
						ttlprop,
						{
							duration : 250,
							easing   : 'easeInSine'
						}
					);
				}
				*/
			}
			
		};
		win_obj.scroll(scrolled);
		setTimeout(function(){
			scrolled();
		}, 1000);
		
		// top .
		$('.totop a').click(function(){
			var that = $(this);
			$('html, body').stop(true).animate({'scrollTop':0}, {'duration':350, 'easing':'easeInSine', complete: function(){
				var anc = that.attr('href');
				window.location.hash = anc;
			}});
			return false;
		});
	}
	
	if(getNintendoType() != 'wii')
	{
		var flashvars = {'page':'mode'};
		var params = { wmode:"transparent", quality:"high"};
		var attributes = {};
		swfobject.embedSWF("../_swf/menu.swf", "flashcontent", "940", "200", "9.0.115", "", flashvars, params, attributes);
	}
	
	var ntype = getNintendoType();
	if(lowievar != ''|| getNintendoType() != '')
	{
		if(ntype != ''&& ntype != 'wiiu')
		{
			$(".iframe1").click(function(){
				document.location = './online1.html';
				$.cookie('bkhref', document.location.href, {expires: 0, path: '/' });
				return false;
			});
			$(".iframe2").click(function(){
				document.location = './tour1.html';
				$.cookie('bkhref', document.location.href, {expires: 0, path: '/' });
				return false;
			});
		}
		else
		{
			
			setTimeout(function(){
				$(".iframe1").colorbox({iframe:true, width:"850px", height:"625px"});
				$(".iframe2").colorbox({iframe:true, width:"850px", height:"600px"});
			}, 1);
		}
	}
	else
	{
		$(".iframe1").attr('href', $(".iframe1").attr('href').replace('online1.html', 'online.html'));
		$('.iframe2').attr('href', $('.iframe2').attr('href').replace('tour1.html', 'tour.html'));
		setTimeout(function(){
			$(".iframe1").colorbox({iframe:true, width:"850px", height:"625px"});
			$(".iframe2").colorbox({iframe:true, width:"850px", height:"600px"});
		}, 1);
	}
	
});


