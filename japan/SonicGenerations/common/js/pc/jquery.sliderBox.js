(function($){
$.fn.sliderBox=function(){

var $slider = $(this);
var slider = this;

var options;
var slideNo;
var width;
var height;
var timer;

//
$slider.wrap('<div class="sliderBox" style="padding:0;margin:0;position:relative;overflow:hidden;"></div>');
$slider.after('<div class="control"><span class="slider_prev">Prev</span><span class="slider_next">Next</span></div>');
$slider.css('position','relative');

var $parent = $($(this).parent());


this.stopTimer=function(){
	$slider.stop();
	clearTimeout(timer);
}
this.init=function(op){
	var defaults={
		speed:800
		,marginWidth:0
		,easing:'easeInOutQuint'
		,control:true
		,auto:true
		,autoTime:9000
	}
	options=$.extend(defaults,op);
	if($('li',slider).children().length == 1){
		options.control = false;
		options.auto = false;
	}
	slideNo = 0;	
	
	width = Math.floor($('li',this).width());
	height = Math.floor($('li',this).height());
	
	$parent.css('width',width+'px');
	$parent.css('height',height+'px');

	width += options.marginWidth;
	
	$slider.append($('li',slider).eq(0).clone());
	$('li',slider).each(function(){
		var index = $(this).index();
		$(this).css({
			'position':'absolute'
			,'top':'0'
			,'left':index * width+'px'
		});
		
	});
	
	if(options.control){
		$('.control',$parent).show();
		$('.slider_next',$parent).click(function(){slider.nextSlide();return false;});
		$('.slider_prev',$parent).click(function(){slider.prevSlide();return false;});
	}else{
		$('.control',$parent).hide();
	}

	if(options.auto){
		timer = setInterval(function(){
			slider.nextSlide();
		},options.autoTime);
	}
	$slider.css('left',slider.getLeft(slideNo));
}

this.nextSlide=function(){
	$slider.filter(':not(:animated)').each(function(){
		if(slideNo >= slider.children().length-1){
			slideNo = 0;
		}
		$slider.css('left',slider.getLeft(slideNo));
		slideNo++;
		
	}).stop(true, false).animate(
		{'left':slider.getLeft(slideNo)+'px'},
		{
			duration: options.speed
			,easing: options.easing
		}
	);
};
this.prevSlide=function(){
	$slider.filter(':not(:animated)').each(function(){
		if(slideNo <= 0){
			slideNo = slider.children().length-1;
		}
		$slider.css('left',slider.getLeft(slideNo));
		slideNo--;
	}).stop(true, false).animate(
		{'left':slider.getLeft(slideNo)+'px'},
		{
			duration: options.speed
			,easing: options.easing
		}
	);
};
this.jumpSlide=function(no){
	slideNo = no;
	$slider.stop(true, false).animate(
		{'left':slider.getLeft(slideNo)+'px'},
		{
			duration: options.speed
			,easing: options.easing
		}
	);
};

this.getLeft=function(number){
	//var w = Math.floor($('li',slider).eq(number).width() * number) * -1;
	var w = Math.floor(width * number) * -1;
	return w;
};


return this;

}})(jQuery);