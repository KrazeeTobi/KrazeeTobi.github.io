(function (lib, img, cjs) {

var p; // shortcut to reference prototypes

// library properties:
lib.properties = {
	width: 940,
	height: 740,
	fps: 60,
	color: "#110000",
	manifest: [
		{src:"image/wave.jpg", id:"wave_1"}
	]
};



// symbols:


(lib.wave_1 = function() {
	this.initialize(img.wave_1);
}).prototype = p = new cjs.Bitmap();
p.nominalBounds = new cjs.Rectangle(0,0,940,940);


(lib.wave_2 = function() {
	this.initialize();

	// レイヤー 1
	this.instance = new lib.wave_1();
	this.instance.setTransform(-470,-470);

	this.addChild(this.instance);
}).prototype = p = new cjs.Container();
p.nominalBounds = new cjs.Rectangle(-470,-470,940,940);


// stage content:
(lib.wave = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// レイヤー 1
	this.instance = new lib.wave_2();
	this.instance.setTransform(480.1,350,0.578,0.578,-71.5);

	this.timeline.addTween(cjs.Tween.get(this.instance).to({regX:-0.1,scaleX:0.79,scaleY:0.79,rotation:10.2,x:469.8,alpha:0},37).to({_off:true},1).wait(62));

}).prototype = p = new cjs.MovieClip();
p.nominalBounds = new cjs.Rectangle(606.2,376.2,687.7,687.7);

})(lib = lib||{}, images = images||{}, createjs = createjs||{});
var lib, images, createjs;