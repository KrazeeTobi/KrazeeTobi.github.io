$(document).ready(function(){
	$(".btnToggle").on("click", function() {
		$(this).prev().slideToggle();
		$(this).toggleClass('openToggle');
	});
});