(function($){
$.fn.accordionMove=function(option){
$action = $(this);
action = this;

var defaults={
	easing:'easeInOutCubic'
	,durationIn:700
	,durationOut:400
	,topmargin:70
	,target:'h4'
	,parent:'h3'
	,cls:'.contensSubstance'
	,pageWait:400
	,read:false
}
var options=$.extend(defaults,option);
var easing;
var target = $(this);
var article = target.next();
var top;
var duration;
var moveAnimation;

$(options.cls,this).hide();
$(options.target,this).addClass('close').css('cursor','pointer');

$(options.target,this).click(function(){
	target = $(this);
	article = target.next();
	moveAnimation = true;
	
	if(article.is(":hidden")){
		duration = options.durationIn;
		top = target.offset().top - options.topmargin;
	}else{
		duration = options.durationOut;
		top = target.offset().top - options.topmargin;
		//top = target.prevAll(options.parent+":first").offset().top - options.topmargin;
		if(top > ($(window).height()-options.topmargin)){
			moveAnimation = false;
		}
	}
	
	if(options.read){
		if(!(article.html().length >= 1) ){
			var filename = target.attr('data');
			article.load(
				filename
				,""
				,function(){
					var backTop = $('article',article).backTop();
					action.windowMove();
				}
			);
		}else{
			action.windowMove();
		}
	}else{
		action.windowMove();
	}
	
	//return false;
});


this.windowMove = function(action){
	if(moveAnimation){
		$('html,body').stop(true, false).animate(
			{'scrollTop':top},
			{
				duration: duration
				,easing: options.easing
			}
			
		);
	}
	article.stop(true, true).slideToggle(
		{
			duration: duration
			,easing: options.easing
			,complete:function(){
				if(article.is(":hidden")){
					target.removeClass('open');
					target.addClass('close');
					article.hide();
				}else{
					target.removeClass('close');
					target.addClass('open');
					article.show();
				}
			}
		}
	);
	return false;
	
}

var url = window.location.hash;
url = url.split("?");
url = url[0].split("#");
var urlHash = url[1];
if(urlHash != undefined){
	setTimeout(function(){
		$('#'+urlHash).prevAll(options.target+":first").trigger('click');
	}, options.pageWait);
}


return this;

}})(jQuery);