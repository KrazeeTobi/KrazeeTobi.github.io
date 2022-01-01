(function($){
$.fn.backTop=function(option){

var defaults={
	easing:'easeInOutCubic'
	,type:'append'
	,duration:500
	,top:0
	,text:'▲トップへ戻る'
	,cls:'backTop'
}
var options=$.extend(defaults,option);

if(options.type == 'append'){
	this.append('<div class="'+ options.cls +'"><a href="javascript:void(0);">'+ options.text +'</a></div>');
}else if(options.type == 'before'){
	this.before('<div class="'+ options.cls +'"><a href="javascript:void(0);">'+ options.text +'</a></div>');
}
$("."+ options.cls+" a").click(function(){
	$('html,body').stop(true, false).animate(
	{'scrollTop':options.top},
	{
		duration: options.duration
		,easing: options.easing
	}
	);
	return false;
});


return this;

}})(jQuery);