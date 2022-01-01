$(document).ready(function() {
	var _url = document.URL;
	var _title = document.title;
	$("#header-twitter").bind("click",{url:_url,title:_title},twitterShare)
	$("#header-facebook").bind("click",{url:_url,title:_title},facebookShare)
	$("#header-google").bind("click",{url:_url,title:_title},googleShare)
	
	function twitterShare(event){
		var _twitterUrl=encodeURI("http://twitter.com/share?url="+event.data.url+"&text="+event.data.title+"&hashtags=SonicChannel");
		window.open(_twitterUrl,"_blank")
	}
	
	function facebookShare(event){
		var _facebookUrl="https://www.facebook.com/sharer/sharer.php?u="+encodeURI(event.data.url);
		window.open(_facebookUrl,"_blank")
	}
	
	function googleShare(event){
		var _googleUrl="https://plus.google.com/share?url={"+encodeURI(event.data.url)+"}";
//		window.open(_googleUrl,'','menubar=no,toolbar=no,resizable=yes,scrollbars=yes,height=600,width=600')
		window.open(_googleUrl,'_blank')
	}
	
});

