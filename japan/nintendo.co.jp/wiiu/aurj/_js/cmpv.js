//2013.11.20ADD
$(function()
{
$('#contents').bind("contextmenu",function(e)
{
return false;
});
});


function lowerAndroid(n) {
	var bo = false;
	var ua = navigator.userAgent.toLowerCase();
	var version = ua.substr(ua.indexOf('android')+8, 3);
	if(ua.indexOf("android")) 
		if(parseFloat(version) < n)
			bo = true;
	return bo;
}

var init_title = document.title;
setInterval(function(){
	document.title = init_title;
}, 1);

function ButtonClickFunc(){
	// Flash ‚ÌƒGƒŒƒƒ“ƒg‚ðŽæ“¾.
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
if(-1 == getNintendoType().indexOf('ds'))
	document.write('<style type="text/css">.bgimg,#externalmov{visibility:hidden;} .listitem{opacity:0;}</style>');
$(function(){
	
	
	
	
	/*
	// ga .
	var gapaths = [];
	gapaths.push('/wiiu/aurj/js/cmpv/bobusrei/index.html');
	gapaths.push('/wiiu/aurj/js/cmpv/speedskeat/index.html');
	gapaths.push('/wiiu/aurj/js/cmpv/carring/index.html');
	gapaths.push('/wiiu/aurj/js/cmpv/figureskeatpai/index.html');
	gapaths.push('/wiiu/aurj/js/cmpv/skicross/index.html');
	gapaths.push('/wiiu/aurj/js/cmpv/suropestyle/index.html');
	gapaths.push('/wiiu/aurj/js/cmpv/pv/index.html');
	*/
	
	if(0 <= getSmartPhoneType().indexOf('android') || 0 <= getSmartPhoneType().indexOf('iP'))
		$('div#externalmov .wiiuplay img').css({visibility:'hidden'});
	
	
	
	var win = $(window);
	var listitems = $('.listitem');
	listitems.css({opacity:0});
	
	if(-1 == getNintendoType().indexOf('ds'))
	{
		$('.limg').each(function(){
			$(this).attr('src', $(this).attr('src').replace(/(.+)_s\.(jpg|png)$/, '$1.$2'));
		});
		$('.movttl,.pagettl').css({opacity:0});
	}
	$('.bgimg,#externalmov').css({visibility:'visible'});
	
	var animFlg = false;
	var externalmovObj = null;
	var movInit = function(){
		externalmovObj = $('#externalmov').clone(true);
	};movInit();
	
	var cngMovTitle = function(key){
		$('.movttl').css({opacity:0});
		$('.movttlimg').attr('src', $('.movttlimg').attr('src').replace(/(.+)(movie_title)\d+(.+)$/, '$1$2'+key+'$3'));
	};
	
	var cngMovTitleFadeCB = function(){
		$('.movttl').animate({opacity: 1,left:'-=70px'},{duration : 400,easing:'easeOutCubic'});
	};
	
	var cngMovTitleFade = function(key){
		$('.movttl').stop(true).animate({opacity: 0},{duration : 300,easing:'easeOutCubic',complete:function(){
			cngMovTitle(key);
			setTimeout(function(){
				$('.movttl').css({left:'+=70px'});
				setTimeout(function(){
					cngMovTitleFadeCB();
				}, 1);
			},1);
		}});
	};
	
	var cngBackground = function(key){
		$('.bgimg').eq(0).attr('src', $('.bgimg').eq(0).attr('src').replace(/(.+\/cm_bg)\d+(.+)/, '$1'+key+'$2'));
	};
	
	var cngBackgroundFade = function(key){
		animFlg = true;
		var obj = $('.bgimg');
		var newObj = obj.clone(true);
		
		obj.before(newObj);
		newObj.css({width:'1920px',position:'absolute', marginLeft: '-960px'});
		cngBackground(key);
		
		obj.stop(true).animate({opacity:0},{duration:1500,easing:'linear',complete:function(){
			$(this).remove();
			animFlg = false;
		}});
	};
	
	var playMov = function(key, func){
		var vtag = '';
		var ntype = getNintendoType();
		
		if(getSmartPhoneType() == 'pc' || lowerAndroid(3))
		{
			if(getNintendoType() == '')
			{
				var flashVars = {moviepath: basepathstr + '/pchigh_cmpv/movie'+ key +'.f4v'};
				if(lowerAndroid(3))
					flashVars.moviepath = WEB_SERVER_BASEPATH + '/mp4cmpv/movie' + key + '.mp4';
					
				var parms = {
					wmode :"transparent",
					Menu :"false",
					allowFullScreen:"true",
					AllowScriptAccess:'always'};
				var attributes = {name:'externalmov'};
				swfobject.embedSWF("../_swf/movieenjoy.swf", "externalmov", "784", "441", "9.0.115", "", flashVars, parms, attributes);
				func();
			}
		}
		else if(0 <= getSmartPhoneType().indexOf('android'))
		{
			vtag = '<video width="725px" height="408px" preload="none" controls="controls" onclick="this.play();" ><source src="' + WEB_SERVER_BASEPATH + '/mp4cmpv/movie' + key + '.mp4"></source></video>';
		}
		else if(0 <= getSmartPhoneType().indexOf('iP'))
			vtag = '<video width="725px" height="408px" preload="none" controls="controls" ><source src="' + WEB_SERVER_BASEPATH + '/ioscmpv/movie' + key + '.m3u8"></source></video>';
		
		
		if(vtag != ''){
			var vobj = $(vtag);
			$('div#externalmov .wiiuplay img').remove();
			$('#externalmov').append(vobj);
			$('#externalmov video').css({marginTop:'85px'});
			
			/*
			setTimeout(function(){
				if(getSmartPhoneType().indexOf('iP') < 0)
					$('#externalmov').find('video').get(0).play();
					func();
			}, 10);
			*/
		}
		else
		{
			setTimeout(function(){
				if(0 < $('div#externalmov').size() && $('object, embed').size() == 0)
				{
					var img = new Image();
					if(getNintendoType() == 'wiiu')
						img.src = '../common/images/cmpv/thum'+key+'_play.jpg';
					else if(-1 == getNintendoType().indexOf('ds'))
						img.src = '../common/images/cmpv/thum'+key+'.jpg';
					else
						img.src = '../common/images/cmpv/thum'+key+'_s.jpg';
						
					$('div#externalmov .wiiuplay img').remove();
					$('div#externalmov .wiiuplay').append($(img));
					
					func();
				}
			}, 1);
		}
	};
	
	var cngPlay = function(key){
		$('#externalmovP').attr('playkey', key+'');
		
		if(key-0 == 1)
			fade_amin($('.btnprev'), false, true);
		else
			fade_amin($('.btnprev'), true, true);
		
		if($('.listitem').size() == key-0)
			fade_amin($('.btnnext'), false, true);
		else
			fade_amin($('.btnnext'), true, true);
		
		setTimeout(function(){
			removeMov();
			addMov(key);
			//if(-1 == getNintendoType().indexOf('ds'))
			if(getNintendoType() == 'wii' || 0 <= getNintendoType().indexOf('ds'))
			{
				//cngBackground(key);
				cngMovTitle(key);
				$('.movttl').css({opacity:1});
			}
			else
			{
				//cngBackgroundFade(key);
				
				if(is_alpha())
					cngMovTitleFade(key);
				else
				{
					cngMovTitle(key);
					$('.movttl').css({opacity:1});
				}
			}
		}, 1);
	};
	
	var itemClickPlay = function(elem){
		cngPlay($(elem).attr('key'));
	};
	
	var removeMov = function(){
		ButtonClickFunc();
		setTimeout(function(){
			$('#externalmov').remove();
		},1);
	};
	
	var addMov = function(key){
		$('#externalmovP').css({visibility:'hidden'});
		setTimeout(function(){
			$('#externalmovP').append(externalmovObj.clone(true));
			playMov(key, function(){
				$('#externalmovP').css({visibility:'visible'});
			});
			
			if(getNintendoType() == 'wiiu')
			{
				$('.wiiuplay').click(function(){
					window.open(WEB_SERVER_BASEPATH + '/wiiucmpv/movie' + $(this).closest('#externalmovP').attr('playkey') + '.m3u8');
					return false;
				});
			}
		},1);
	};
	
	var nextprevBtn = function(obj){
		var oldKey = $('#externalmovP').attr('playkey');
		if(0 <= obj.attr('class').indexOf('btnprev'))
		{
			if(oldKey != '1')
				$('.listitem').eq((oldKey-0)-2).find('.tab').click();
		}
		else
		{
			if($('.listitem').size() != oldKey-0)
				$('.listitem').eq((oldKey-0)).find('.tab').click();
		}
	};
	
	var fastFlg = false;
	$('.tab').click(function(){
		if(!animFlg)
		{
			// ga.
			//_gaq.push(['_trackPageview',gapaths[($(this).attr('key') - 1)]]);
			
			if(-1 == getNintendoType().indexOf('ds'))
			{
				$('.tab').find('img').attr('tab', 'f');
				$('.tab').each(function(){
					$(this).find('img').attr('src', $(this).find('img').attr('src').replace(/_o\.(jpg|png|gif)$/, '.$1'));
				});
				
				var obj = $(this);
				var imgobj = obj.find('img');
				imgobj.attr('tab', 't');
				
				if(!imgobj.attr('src').match(/_o\.(jpg|png|gif)$/))
					imgobj.attr('src', imgobj.attr('src').replace(/\.(jpg|png|gif)$/, '_o.$1'));
			}
			
			if($(this).attr('key') != $('#externalmovP').attr('playkey') || !fastFlg)
				itemClickPlay(this);
			
			fastFlg = true;
			
			if(getNintendoType() == 'wiiu')
				return true;
		}
		return false;
	});
	
	
	
	if(-1 == getNintendoType().indexOf('ds'))
	{
		//$('#cmpvcontainer').css({backgroundColor: '#C7DDF5', height:'100%'});
		$('#contents,#cmpvcontainer').css('overflow','hidden');
		$('.bgimg').css({width:'1920px',position:'absolute', marginLeft: '-960px'});
		//$('body,#cmpvcontainer,#contents').css('overflow-x','hidden');
		
		$('.imgover').hover(
			function(){
				if($(this).attr('tab') != 't')
					$(this).attr('src', $(this).attr('src').replace(/\.(jpg|png|gif)$/, '_o.$1'));
			},
			function(){
				if($(this).attr('tab') != 't')
					$(this).attr('src', $(this).attr('src').replace(/_o\.(jpg|png|gif)$/, '.$1'));
			}
		);
		
		if(lowievar != '6' && getNintendoType() == '')
		{
			$('.movBtn').click(function(){
				if(!animFlg)
					nextprevBtn($(this));
				return false;
			});
			fade_amin($('.btnnext'), true, true);
		}
	}
	
	
	
	
	var initAnimFlg = false;
	var initListItem = function(){
		listitems.css({position:'relative', left:'50px'});
		listitems.each(function(ii){
			$(this).delay(ii*200).animate({left:'0px', opacity:1},{duration:300,easing:'easeOutQuart'});
		});
	};
	
	var scrollCheck = function(){
		if(!initAnimFlg)
		{
			var sb = win.scrollTop() + win.height();
			var top = listitems.eq(0).offset().top + listitems.eq(0).height();
			if(top < sb)
			{
				initAnimFlg = true;
				initListItem();
			}
		}
	};
	
	if(animenabled_flg)
	{
		setTimeout(function(){
			scrollCheck();
			win.scroll(scrollCheck);
		}, 1500);
		
		$('.pagettl').css({marginLeft:'+=150px'});
		setTimeout(function(){
			if(!is_alpha())
				$('.pagettl').css({opacity:1});
			setTimeout(function(){
				$('.pagettl').animate({marginLeft:'-=150px', opacity:1},{duration:350,easing:'easeOutQuart'});
			},1);
		},1500);
	}
	else
	{
		initAnimFlg = true;
		listitems.css({opacity:1});
		$('.movttl,.pagettl').css({opacity:1});
	}
	
	if(lowievar == '6')
		DD_belatedPNG.fix('img, .png-bg');
	
	$('.btnprevp,.btnnextp').css('display', 'none');
	
	setTimeout(function(){
		$('.tab').eq(0).click();
	}, 10);
	
	
	var initFlg = false;
	if(animenabled_flg)
	{
		// top .
		$('.totop a').click(function(){
			var that = $(this);
			$('html, body').stop(true).animate({'scrollTop':0}, {'duration':350, 'easing':'easeInSine', complete: function(){
				var anc = that.attr('href');
				window.location.hash = anc;
			}});
			return false;
		});
		
		/*
		var movttlTop = $('#movttl').offset().top;
		listitems.find('a').click(function(){
			if(initFlg)
			{
				var that = $(this);
				$('html, body').stop(true).animate({'scrollTop':movttlTop}, {'duration':350, 'easing':'easeInSine', complete: function(){
					var anc = that.attr('href');
					window.location.hash = anc;
					
				}});
			}
			else
				initFlg = true;
			return false;
		});
		*/
	}
	
	
	//alert($('.bgimg').attr('src'));
});







