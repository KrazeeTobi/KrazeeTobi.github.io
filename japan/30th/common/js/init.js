$(document).ready(function() {
	
	$('.inView').on('inview', function(event, isInView, visiblePartX, visiblePartY) {
		if(isInView){
			$(this).stop().delay(500).queue(function() {
				$(this).addClass('active').dequeue();
			});
		}else{
			$(this).stop().removeClass('active');
		}
	});
	$('#contents-topics ul li').wrapInner('<div class="moveX"><div class="moveY"><div class="liBody"></div></div></div>');
	$('#contents-illust ul li').wrapInner('<div class="moveX"><div class="moveY"><div class="liBody"></div></div></div>');
});