(function($){
$.fn.paging=function(option){

var defaults={
	count:10//表示件数
	,disp:10//数字表示数
	,cls:'paging'
	,nocls:'pageno'
	,noPageVisible:true
	,toNowlink:'nowlink'
	,toPagelink:'pagelink'
}
var options=$.extend(defaults,option);
var obj = this;
var $obj = $(this);
var parent =this.parent();
obj.strCreate = function(_limit, _page){
	if(_limit <= 1) return "";
	
	_text = "";
	_page = Number(_page);
	var _next = _page+1;
	var _prev = _page-1;
	var _start =1;
	var _end = 1;
	
	//ページ番号リンク用
	//始点
	if(_page - Math.floor(options.disp/2)> 0){
		_start = (_page-Math.floor(options.disp/2));
		
	}
	//終点
	if(_start> 1){
		_end =  (_page+Math.floor(options.disp/2))
	}else{
		_end =  options.disp;
	}
	//始点再計算
	if(_limit <_end){
		_start = _start-(_end-_limit);
	}else{
		_start = _start;
	}
	
	//最初のページへのリンク
	if(_page != 1){
		_text+= '<a href="javascript:void(0)" data="1">&lt;&lt;</a>';
		_text+= '<a href="javascript:void(0)" data="'+_prev+'">&lt;</a>';
	}else if(options.noPageVisible){
		_text+= '<span>&lt;&lt;</span>';
		_text+= '<span>&lt;</span>';
	}
	
	if(_start > Math.floor(options.disp/2)){
		_text+= "...";
	}
	
	//ページ
	for(var i=_start; i <= _end ; i++){
		var class1 = '';
		var class2 = '';
		if(page == i){
			class1 = options.toPagelink;
		}
		if(_page == i){
			class2 = options.toNowlink;
		}
		if(i <= _limit && i> 0 ) _text+= '<a href="javascript:void(0)" data="'+i+'" class="'+class1+' '+class2+'">'+i+'</a>';
	}
	
	if(_limit > _end){
		_text+= "...";
	}
	//最後のページへのリンク
	if(_page!= _limit){
		_text+= '<a href="javascript:void(0)" data="'+_next+'">&gt;</a>';
		_text+= '<a href="javascript:void(0)" data="'+_limit+'">&gt;&gt;</a>';
	}else if(options.noPageVisible){
		_text+= '<span>&gt;</span>';
		_text+= '<span>&gt;&gt;</span>';
	}
	//_text.='('._start.' - '._end.')';
	_text += '<span class="'+options.nocls+'">'+ _page +'/'+ _limit +'</span>';
	return _text;
}

$('.'+options.cls+' a').live("click",function(){
	$('li',obj).hide();
	var p = $(this).attr('data');
	if(!p) return false;
	p = Number(p);
	var _start = Number(p * options.count - options.count);
	for(var i=1;i<=options.count;i++){
		var n = limit - Number(i+_start);
		if(n < 0){break;}
		$('li',obj).eq(Number(n)).show();
	}
	var tt = obj.strCreate(limitPage,p);
	$('.'+options.cls+'',parent).html(tt);
});


var fineName = window.location.href.match(/\d{3}/i);
var fileNo = Number(fineName);
var page = Math.ceil(fileNo/options.count);
var limit = $('li',this).size();
var limitPage = Math.ceil(limit/options.count);

//menu
var tt = obj.strCreate(limitPage,page);
$("#contents-navigation ul").before('<div class="'+options.cls+'">'+tt+'</div>');


$('li',obj).eq((limit-fileNo)).css('background','#ff9900').find('a').css('color','#000000');

$('.'+options.cls+' a').attr('data',page).trigger('click');

	
return this;

}})(jQuery);