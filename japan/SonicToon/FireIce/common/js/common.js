$(document).ready(function() {
	$(".swipeBox").swipebox({
		useSVG : false
	});
	
	if($('#main-smartphone').is(':hidden')){
		init()
		.then(anime1)
		.then(anime2)
		.then(anime3)
		.then(anime4)
		.then(anime5)
		.then(anime6)
	}
});

/*--------------------------------------------------------------------------//
//  初期化
//--------------------------------------------------------------------------*/
function init(){
	var _defer = new $.Deferred;
	$('h1').css({"transform":"scale(0.01)"}).hide();
	$('#main-image').css({"transform":"scale(0.01) rotate(180deg)"}).hide();
	$('#logo-n3ds').hide();
	$('#main-copy').css({"opacity":0,"bottom":150}).hide();
	$('#main-movie').css({"opacity":0,"right":100}).hide();
	$('#main-info').hide();
	_defer.resolve();
	return _defer.promise();
}

/*--------------------------------------------------------------------------//
//  アニメ１
//--------------------------------------------------------------------------*/
function anime1(){
	var _defer = new $.Deferred;
//	$('#main-image').delay(0).animate({"display":"none"},function(){
	$('#main-image').delay(500).animate({"display":"none"},function(){
		_defer.resolve();
	});
	return _defer.promise();
}

/*--------------------------------------------------------------------------//
//  アニメ2
//--------------------------------------------------------------------------*/
function anime2(){
	var _defer = new $.Deferred;
	$('#main-image').show()
	.animate({
		transform: 'rotate(360deg) scale(1)'
		
		}, 500,"easeOutBack", function() {
			_defer.resolve();
	});
	return _defer.promise();
}


/*--------------------------------------------------------------------------//
//  アニメ3
//--------------------------------------------------------------------------*/
function anime3(){
	var _defer = new $.Deferred;
	$('h1').show()
	.animate({
		transform: 'scale(1)'
		
		}, 1000,"easeOutElastic", function() {
			_defer.resolve();
	});
	return _defer.promise();
}


/*--------------------------------------------------------------------------//
//  アニメ4
//--------------------------------------------------------------------------*/
function anime4(){
	var _defer = new $.Deferred;
	$('#main-copy').show()
	.animate({
		"opacity":1,
		"bottom":175
		}, 1000,"easeOutQuart", function() {
			_defer.resolve();
	});
	return _defer.promise();
}


/*--------------------------------------------------------------------------//
//  アニメ5
//--------------------------------------------------------------------------*/
function anime5(){
	var _defer = new $.Deferred;
	$('#main-info').fadeIn();
	$('#logo-n3ds').fadeIn();
	$('#main-movie').show()
	.animate({
		"opacity":1,
		"right":0
		}, 500,"easeOutBack", function() {
			_defer.resolve();
	});
	return _defer.promise();
}

/*--------------------------------------------------------------------------//
//  アニメ6
//--------------------------------------------------------------------------*/
function anime6(){
	var _defer = new $.Deferred;
	canvas = document.getElementById("main-canvas");
	images = images||{};

	var loader = new createjs.LoadQueue(false);
	loader.addEventListener("fileload", handleFileLoad);
	loader.addEventListener("complete", handleComplete);
	loader.loadManifest(lib.properties.manifest);
	_defer.resolve();
	return _defer.promise();
}


/*--------------------------------------------------------------------------//
//  Canvas
//--------------------------------------------------------------------------*/
function handleFileLoad(evt) {
	if (evt.item.type == "image") { images[evt.item.id] = evt.result; }
}

function handleComplete() {
	exportRoot = new lib.wave();

	stage = new createjs.Stage(canvas);
	stage.addChild(exportRoot);
	stage.update();

	createjs.Ticker.setFPS(lib.properties.fps);
	createjs.Ticker.addEventListener("tick", stage);
}