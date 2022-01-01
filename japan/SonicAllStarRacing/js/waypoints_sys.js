$(document).ready(function() {
	$('.top').addClass('hidden');
	$.waypoints.settings.scrollThrottle = 30;
	$('#container').waypoint(function(event, direction) {
		$('.top').toggleClass('hidden', direction === "up");
	}, {
		offset: '-100%'
	//}).find('#main-nav-holder').waypoint(function(event, direction) {
		}).find('#main-nav-holder').waypoint(function(event, direction) {
		$(this).parent().toggleClass('sticky', direction === "down");
		event.stopPropagation();
	});
});