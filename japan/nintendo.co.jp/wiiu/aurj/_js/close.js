
// init .
$(function(){
	
	$('.close a').click(function(){
		if($.cookie('bkhref'))
			document.location.href = $.cookie('bkhref');
		else
			document.location.href = './';
		
		/*
		if(0 <= document.referrer.indexOf(document.location.hostname))
			history.go(-1);
		else
			document.location.href = '../';
		*/
		
		return false;
	});
	
	$('#online, #tour').css('width', '+=1');
	setTimeout(function(){$('#online').css('width', '-=1');}, 1);
	
});





