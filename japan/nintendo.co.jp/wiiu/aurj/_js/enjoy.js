
var init_title = document.title;
setInterval(function(){
	document.title = init_title;
}, 1);

function jsstart(){
	{}
	//alert(sideBtnDisplayProp);
	//if(getSmartPhoneType() == 'pc')
	//	$('.btn-nextmovie, .btn-prevmovie').css('display', sideBtnDisplayProp);
}


function ButtonClickFunc(){
	// Flash ÇÃÉGÉåÉÅÉìÉgÇéÊìæ.
	var swf = DocumentGetElementFromName('externalmov');
	if(swf)
	{
		if(swf.tagName.toLowerCase() == 'object'){
			swf.jsstop();
		}
	}
}

function DocumentGetElementFromName(name) {
	var obj;
	if (navigator.appName.indexOf("Microsoft") != -1)
		obj = window[name];
	else
		obj = document[name];
	
	if(!obj)
		return null;
	
	return obj;
}


// init .
var formal_selected_key = ''; 
var plaingiconchng = null;
document.write('<style type="text/css">#Container .enjoy ul li.movie-box{display:block;}</style>');
$(function(){
	
	
	
	var formals = $('.list-formal .formal-item:not(.movie-box), .list-dream .dream-item');
	
	if(lowievar == '6' || getNintendoType() != '')
	{
		$('.btn-prevmovie, .btn-nextmovie').remove();
	}
	
	if(0 <= getNintendoType().indexOf('ds'))
	{
		$('.simg').each(function(){
			$(this).attr('src', $(this).attr('src').replace(/\.(jpg|png)$/, '_s.jpg'));
		});
		$('.spng').each(function(){
			$(this).attr('src', $(this).attr('src').replace(/\.png$/, '_s.png'));
		});
	}
	
	if(-1 == getNintendoType().indexOf('ds'))
	{
		$('.imgover').hover(
			function(){$(this).attr('src', $(this).attr('src').replace(/.(jpg|png|gif)$/, '_o.$1'));},
			function(){$(this).attr('src', $(this).attr('src').replace(/_o.(jpg|png|gif)$/, '.$1'));}
		);
	}
	
	
	// ga .
	var gapaths = [];
	gapaths.push('/wiiu/aurj/js/enjoy/alpine/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/skijumpingrafle/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/mogule/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/skicross/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/baiasuron/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/pararerudaikaiten/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/suropestyle/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/snowboadcross/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/speedskeat/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/shorttruk/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/figureskeat/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/figureskeatpai/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/sochi/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/bobusrei/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/icehokkei/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/carring/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/wintersportschampion/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/groupsnoboad/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/musicalfigure/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/streeticehokkei/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/jetcoaster/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/holeinone/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/snowmedalyukigassen/index.html');
	gapaths.push('/wiiu/aurj/js/enjoy/bakusoukira/index.html');
	
	
	//var formal_movie_box_open_prop = {height: $('.movie-box').outerHeight()};
	var formal_movie_box_open_prop = {height: '750px'};
	var formal_movie_box_close_prop = {height: '0px'};
	var formal_movie_box_duration = 250;
	var formal_movie_box = $('.movie-box').clone(true);
	formal_movie_box.css(formal_movie_box_close_prop).css('display', 'block');
	$('.movie-box').css(formal_movie_box_close_prop);
	$('.movie-box').eq(1).remove();
	$('.movie-box .movarea').eq(0).attr('id', 'externalmov');
	formal_movie_box.find('.movarea').attr('id', 'externalmov');
	var oldcnt = 0;
	
	var movchange = function(tcnt, key, last_flg, obj){
		var new_moviekey = 1;
		if(tcnt <= 16)
			new_moviekey = 0;
		
		
		var new_movie = formal_movie_box.eq(new_moviekey).clone(true);
		new_movie.find('.movarea').attr('id', 'externalmov');
		var ttl_obj = $('.movie-box-ttl', new_movie);
		var howto_obj = $('.movie-box-howto', new_movie);
		var txt_obj = $('.movie-box-txt', new_movie);
		
		if(-1 == getNintendoType().indexOf('ds'))
		{
			ttl_obj.attr('src', ttl_obj.attr('src').replace(/\d+b\.(jpg|png|gif)$/, key+'b.$1'));
			txt_obj.attr('src', txt_obj.attr('src').replace(/\d+\.(jpg|png|gif)$/, key+'.$1'));
			howto_obj.attr('src', howto_obj.attr('src').replace(/\d+\.(jpg|png|gif)$/, key+'.$1'));
		}
		else
		{
			ttl_obj.attr('src', ttl_obj.attr('src').replace(/\d+b\.(jpg|png|gif)$/, key+'b_s.jpg'));
			txt_obj.attr('src', txt_obj.attr('src').replace(/\d+\.(jpg|png|gif)$/, key+'_s.jpg'));
			howto_obj.attr('src', howto_obj.attr('src').replace(/\d+\.(jpg|png|gif)$/, key+'_s.jpg'));
		}
		
		new_movie.attr('key', formal_selected_key);
		
		if(getNintendoType() == 'wii')
		{
			$('div#externalmov img', new_movie).attr('src', '../common/images/enjoy/subimage'+key+'.jpg');
		}
		
		
		if(tcnt == 16)
			formals.eq(15).after(new_movie);
		else if(last_flg)
			obj.after(new_movie);
		else
			obj.before(new_movie);
		
		
		// mov .
		var vtag = '';
		var ntype = getNintendoType();
		var nomovieflg = true;
		
		if(getSmartPhoneType() == 'pc')
		{
			if(getNintendoType() != 'wii' && -1 == getNintendoType().indexOf('ds'))
			{
				var flashVars = {moviepath: basepathstr + '/pchigh_enjoy/movie'+ key +'.f4v'};
				var parms = {
					wmode :"transparent",
					Menu :"false",
					allowFullScreen: "true",
					AllowScriptAccess : 'always'};
				var attributes = {name:'externalmov'};
				
				//swfobject.embedSWF("../_swf/movie"+key+".swf", "mov", "784", "441", "9.0.115", "", flashVars, parms, attributes);
				swfobject.embedSWF("../_swf/movieenjoy.swf", "externalmov", "784", "441", "9.0.115", "", flashVars, parms, attributes);
			}
		}
		else if(0 <= getSmartPhoneType().indexOf('android')){
			vtag = '<video width="725px" height="408px" preload="none" controls="controls" onclick="this.play();" ><source src="' + WEB_SERVER_BASEPATH + '/mp4/movie' + key + '.mp4"></source></video>';
		}else if(0 <= getSmartPhoneType().indexOf('iP'))
			vtag = '<video width="725px" height="408px" preload="none" controls="controls" ><source src="' + WEB_SERVER_BASEPATH + '/ios/movie' + key + '.m3u8"></source></video>';
		
		if(vtag != ''){
			
			var vobj = $(vtag);
			new_movie.find('.movarea').append(vobj);
			/*
			setTimeout(function(){
				if(getSmartPhoneType().indexOf('iP') < 0)
					new_movie.find('video').get(0).play();
			}, 10);
			*/
		}
		else
		{
			setTimeout(function(){
				if(0 < $('div#externalmov').size() && $('object, embed').size() == 0)
				{
					var img = new Image();
					if(-1 == getNintendoType().indexOf('ds'))
						img.src = '../common/images/enjoy/subimage'+key+'.jpg';
					else
						img.src = '../common/images/enjoy/subimage'+key+'_s.jpg';
					
					$('div#externalmov img').remove();
					$('div#externalmov').append($(img));
				}
			}, 1);
		}
		
		return new_movie;
	};
	
	
	var movchangetop = function(key){
		var ancobj = $('[key="'+key+'"]');
		var scrollval =  ancobj.offset().top;
		
		
		$('html, body').stop(true).animate({'scrollTop':ancobj.offset().top}, {'duration':300, 'easing':'easeInSine', complete: function(){
			
			if(-1 == getNintendoType().indexOf('ds'))
			{
				var anc = $('[key="'+key+'"]').attr('id');
				//window.location.hash = '#' + anc;
				navcompany_flg = true;
			}
			
			if(lowievar == '6')
			{
				/*
				$('#nav').css('position', 'rerative');
				setTimeout(function(){
					$('#nav').css('position', 'absolute');
				}, 1);
				*/
				$('h3').css('width', '+=1px');
				$('#nav').css('width', '+=1px');
				setTimeout(function(){
					$('h3').css('width', '-=1px');
					$('#nav').css('width', '-=1px');
				}, 1);
			}
		}});
		
		return false;
	};
	
	
	
	/*
	if(lowievar == '6')
	{
		$(window).scroll(function(){
			$('#nav').css({'position': 'absolute', 'bottom': 0});
			/*
			$('#nav').css('position', 'rerative');
			setTimeout(function(){
				$('#nav').css('position', 'absolute');
			}, 1);
		});	
	}
	*/
	
	plaingiconchng = function(key){
		
		var cnt = 1;
		formals.each(function(){
			//$(this).find('.plaingIcon').css('visibility', 'hidden');
			$(this).css('background-image', $(this).css('background-image').replace(/(url.+)_p(.+)/, '$1$2'));
			$('#a'+cnt+' img').attr('src', $('#a'+cnt+' img').attr('src').replace(/(_o|_p)/, ''));
			cnt++;
		});
		
		if(key != '')
		{
			var objkey = key - 1;
			var tgt = formals.eq(objkey);
			//tgt.find('.plaingIcon').css('visibility', 'visible');
			tgt.css('background-image', tgt.css('background-image').replace(/(_s)?\.(jpg|png)/, '_p$1.$2'));
			$('#a'+key+' img', tgt).attr('src', $('#a'+key+' img', tgt).attr('src').replace(/(_s)?\.(jpg|png)/, '_p$1.$2'));
		}
	};
	
	
	var closeanimcomp = function(tcnt, key, last_flg, obj){
		if($('video').size())
		{
			$('video')[0].pause();
			$('video').attr('muted', 'muted');
		}
		$('.movie-box').remove();
		var new_movie = movchange(tcnt, key, last_flg, obj);
		if(key == 1)
			new_movie.find('.btn-prevmovie').css('display', 'none')
		if(key == 24)
			new_movie.find('.btn-nextmovie').css('display', 'none')
		$('.movie-title, .txt-lead, .txt-howto', new_movie).css('visibility', 'hidden');
		return new_movie;
	};
	
	var openanimcomp = function(key, new_movie){
		setTimeout(function(){
			$('.movie-title, .txt-lead, .txt-howto', new_movie).css('visibility', 'visible');
			plaingiconchng(key);
			movchangetop(key);
		}, 450);
	};
	
	
	var formal_movie_opener = function(height, key, type){
		
		var add_flg = true;
		var item_num = formals.size();
		var cnt = 0;
		
		formals.each(function(){
			if(height < $(this).offset().top || item_num-1 == cnt)
			{
				
				
				
				if(add_flg)
				{
					navcompany_flg = false; // common .
					add_flg = false;
					
					var obj = $(this);
					var last_flg = false;
					var tcnt = cnt;
					
					if(item_num-1 == tcnt)
						last_flg = true;
					
					
					if(oldcnt != tcnt)
					{
						oldcnt = tcnt;
						
						if(getSmartPhoneType() == 'pc' && getNintendoType() == '')
						{
							$('.movie-box').stop(true).animate(
								formal_movie_box_close_prop,
								{
									duration : formal_movie_box_duration,
									easing : 'easeOutCubic',
									complete : function(){
										
										if(getSmartPhoneType() == 'pc' && getNintendoType() == '')
											ButtonClickFunc();
										
										var new_movie = closeanimcomp(tcnt, key, last_flg, obj);
										new_movie.animate(
											formal_movie_box_open_prop,
											{
												duration : formal_movie_box_duration,
												easing   : 'easeInCubic',
												complete : function(){
													openanimcomp(key, new_movie);
													moviebox_next_flg = true;
												}
											});
									}
								});
						}
						else
						{
							$('.movie-box').css(formal_movie_box_close_prop);
							var new_movie = closeanimcomp(tcnt, key, last_flg, obj);
							new_movie.css(formal_movie_box_open_prop);
							openanimcomp(key, new_movie);
							moviebox_next_flg = true;
						}
					}
					else
					{
						oldcnt = tcnt;
						var oldmov = $('.movie-box');
						oldmov.css(formal_movie_box_close_prop);
						
						if(getSmartPhoneType() == 'pc' && getNintendoType() == '')
							ButtonClickFunc();
						
						if($('video').size())
						{
							$('video')[0].pause();
							$('video').attr('muted', 'muted');
						}
						oldmov.remove();
						
						var new_movie = movchange(tcnt, key, last_flg, obj);
						
						if(key == 1)
							new_movie.find('.btn-prevmovie').css('display', 'none')
						if(key == 24)
							new_movie.find('.btn-nextmovie').css('display', 'none')
						
						new_movie.css(formal_movie_box_open_prop);
						$('.movie-title, .txt-lead, .txt-howto', new_movie).css('visibility', 'hidden');
						setTimeout(function(){
							$('.movie-title, .txt-lead, .txt-howto', new_movie).css('visibility', 'visible');
							plaingiconchng(key);
							moviebox_next_flg = true;
						}, 600);
						
					}
				}
			}
			cnt++;
		});
	};
	
	$('.btn-formal').click(function(){
		var obj = $(this);
		var now_key = obj.attr('key');
		var ntype = getNintendoType();
		
		
		// ga.
		_gaq.push(['_trackPageview',gapaths[now_key - 1]]);
		
		
		if(ntype == 'wiiu'){
			window.open(WEB_SERVER_BASEPATH + '/wiiu/movie' + now_key + '.m3u8');
			return false;
		}
		/*
		else if((0 <= getSmartPhoneType().indexOf('iP')))
		{
			window.open(WEB_SERVER_BASEPATH + '/ios/movie' + now_key + '.m3u8');
			return false;
		}
		*/
		
		if(formal_selected_key != now_key)
		{
			formal_selected_key = obj.attr('key');
			formal_movie_opener(obj.closest('.formal-item').offset().top, now_key, 'f');
		}
		return false;
	});
	
	$('.btn-dream').click(function(){
		var obj = $(this);
		var now_key = obj.attr('key');
		var ntype = getNintendoType();
		
		
		// ga.
		_gaq.push(['_trackPageview',gapaths[now_key - 1]]);
		
		
		if(ntype == 'wiiu'){
			window.open(WEB_SERVER_BASEPATH + '/wiiu/movie' + now_key + '.m3u8');
			return false;
		}
		/*
		else if((0 <= getSmartPhoneType().indexOf('iP')))
		{
			window.open(WEB_SERVER_BASEPATH + '/ios/movie' + now_key + '.m3u8');
			return false;
		}
		*/
		
		if(formal_selected_key != now_key)
		{
			formal_selected_key = obj.attr('key');
			formal_movie_opener(obj.closest('.dream-item').offset().top, now_key, 'd');
		}
		return false;
	});
	
	$('.thuma').click(function(){
		$(this).closest('dl').find('[key]').click();
		return false;
	});
	
	
	
	
	
	
	
	
	
	if(animenabled_flg)
	{
		var scroll_items = formals;
		var scrollCheck = function(){
			var sb = $(window).scrollTop() + $(window).height();
			var delay = 0;
			scroll_items.each(function() {
				var obj = $(this);
				if(obj[0].animated)
					return;
				
				var top = obj.offset().top + obj.height();
				if(top < sb)
				{
					obj[0].animated = true;
					var chld = $('dl', obj);
					obj.css('opacity', 0);
					obj.css('left', 50);
					setTimeout(function(){
						obj.stop(true).css('visibility', 'visible').animate({'left': 0, 'opacity': 1}, {'duration': 300, 'easing':'easeOutQuart'});
					}, delay);
					
					var btn = $('.btn-formal, .btn-dream', obj);
					btn.css('position', 'relative');
					btn.css('opacity', 0).css('visibility', 'hidden');
					btn.css('left', btn.width() / 4);
					setTimeout(function(){
						btn.stop(true).css('visibility', 'visible').animate({'left': 0, 'opacity': 1}, {'duration': 300, 'easing':'easeOutQuart'});
					}, delay + 200);
					delay += 100;
				}
			});
		};
		scroll_items.css('visibility', 'hidden');
		setTimeout(function(){
			$(window).scroll(scrollCheck);
			scrollCheck();
		}, 2000);
		
		
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
			
			obj.css('left' , charattl_offset);
			
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
		charattl_anim();
		charatxt_anim();
		
		// top .
		$('.totop a').click(function(){
			var that = $(this);
			$('html, body').stop(true).animate({'scrollTop':0}, {'duration':350, 'easing':'easeInSine', complete: function(){
				var anc = that.attr('href');
				//window.location.hash = anc;
			}});
			return false;
		});
		
	}
	
	
	
	setTimeout(function(){
		if(document.location.hash.match(/enjoy/))
			$('[key="'+document.location.hash.replace('#enjoy', '')+'"]').click();
	}, 1);
	
	
	
	if(getNintendoType() != 'wii' && !getSmartPhoneType().match(/android/))
	{
		var flashvars = {'page':'enjoy'};
		var params = { wmode:"transparent", Menu:"false", quality:"high"};
		var attributes = {};
		swfobject.embedSWF("../_swf/menu.swf", "flashcontent", "940", "200", "9.0.115", "", flashvars, params, attributes);
		
		var flashvars2 = {};
		var params2 = { wmode:"transparent", Menu:"false", quality:"high"};
		var attributes2 = {};
		swfobject.embedSWF("../_swf/enjoytop.swf", "flash-area", "480", "270", "9.0.115", "", flashvars2, params2, attributes);
	}
	
	if(lowievar == '6')
		DD_belatedPNG.fix('img, .png-bg');
	
});


function moviebox_close(elem){
	plaingiconchng('');
	formal_selected_key = '';
	var flobj = $('.movie-box object, .movie-box embed');
	if(0 < flobj.size())
		flobj.remove();
	
	if($('video').size())
	{
		$('video')[0].pause();
		$('video').attr('muted', 'muted');
	}
	
	var obj = $(elem).closest('.movie-box');
	obj.stop(true).animate(
			{height: '0px'},
			{
				duration : 250,
				easing   : 'easeOutCubic',
				step     : function(step){},
				complete : function(){}
			});
		return false;
}

var moviebox_next_flg = true;
function moviebox_next(elem, flg){
	
	if(moviebox_next_flg)
	{
		moviebox_next_flg = false;
		
		var formals = $('.list-formal .formal-item:not(.movie-box), .list-dream .dream-item');
		var obj = $(elem);
		var boxobj = obj.closest('.movie-box');
		var nextkey = 1;
		
		if(flg == 't')
		{
			nextkey = (boxobj.attr('key') - 0) + 1;
			if(formals.size() < nextkey)
				nextkey = 1;
		}
		else
		{
			nextkey = boxobj.attr('key') - 1;
			if(nextkey == 0)
				nextkey = formals.size(); 
		}
		
		formals.find('[key="'+nextkey+'"]').click();
	}
	return false;
}







