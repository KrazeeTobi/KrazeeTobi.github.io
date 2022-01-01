/*
 * 	Ex Equal Height 0.1.0 - jQuery plugin
 *	written by Cyokodog	
 *
 *	Copyright (c) 2012 Cyokodog (http://d.hatena.ne.jp/cyokodog/)
 *	Dual licensed under the MIT (MIT-LICENSE.txt)
 *	and GPL (GPL-LICENSE.txt) licenses.
 *
 *	Built for jQuery library
 *	http://jquery.com
 *
 */
(function($){
	$.ex = $.ex || {};
	$.ex.equalHeight = function(targets,option){
		var o = this,
		c = o.config = $.extend({},$.ex.equalHeight.defaults,option);
		c.targets = targets;

		if(c.watchHeight == 'auto' && c.windowResizeAdjust == 'auto'){
			c.watchHeight = false;
		}
		else
		if(c.watchHeight == true && c.windowResizeAdjust == 'auto'){
			c.windowResizeAdjust = false;
		}
		if(c.watchWrapper == 'auto' && !c.watchHeight){
			c.watchWrapper = false;
		}
		if(c.watchWrapper){
			c.wrappers = c.targets.wrapInner('<div/>').children();
			o.adjustHeight();
			o.saveWrapperHeight();
			var watch = function(){
				setTimeout(function(){
					o.adjust();
					watch();
				},c.watchDelay);
			}
			watch();
		}

		if(c.windowResizeAdjust){
			$(window).resize(function(){
				if(c._resizeTimer) clearTimeout(c._resizeTimer);
				c._resizeTimer = setTimeout(function(){
					o.adjust();
				},c.windowResizeDelay);
			});
		}
		o.adjust();
	};
	$.ex.equalHeight.prototype = {
		saveWrapperHeight : function(){
			var o = this, c = o.config;
			c.wrappers.each(function(idx){
				var target = c.wrappers.eq(idx);
				target.data('ex-equal-height',target.height());
			});
		},
		isResizeWrapper : function(){
			var o = this, c = o.config;
			var ret = false;
			c.wrappers.each(function(idx){
				var target = c.wrappers.eq(idx);
				if(target.height() != target.data('ex-equal-height')){
					ret = true;
				}
			});
			return ret;
		},
		adjust : function(){
			var o = this, c = o.config;
			if(!c.watchWrapper){
				o.adjustHeight();
			}
			else{
				if(o.isResizeWrapper()){
					o.adjustHeight();
					o.saveWrapperHeight();
					c.watchCallback.call(o,o);
				}
			}
		},
		adjustHeight : function(){
			var o = this, c = o.config;
			var max = 0;
			c.targets.each(function(){
				var target = $(this);
				var height = target.css('height','auto').height();
				if(height > max) max = height;
			});
			c.targets.css({
				'height' : max
			});
		}
	}
	$.ex.equalHeight.defaults = {
		api : false,
		watchHeight : 'auto',
		watchDelay : 500,
		watchWrapper : 'auto',
		watchCallback : function(api){},
		windowResizeAdjust : 'auto',
		windowResizeDelay : 100
	};
	$.fn.exEqualHeight = function(option){
		option = option || {};
		var api = new $.ex.equalHeight(this,option);
		return option.api ? api : this;
	};
})(jQuery);

