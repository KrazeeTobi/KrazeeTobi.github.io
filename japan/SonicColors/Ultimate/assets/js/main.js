$(function () {	
	var on = "is-on"

	/*+++++
	pageスクロール
	+++++*/
	var $htBody = $('html,body'),
		$pageLinks = $(".pageLinks");
	var pageMoving = function (ad) {
		var twoffset = $(ad).offset().top;
		$htBody.animate({
			scrollTop: twoffset - 80
		}, 600);
	}
	$pageLinks.on("click", function () {
		pageMoving(this.hash)
	});

	/*+++++
	popchara
	+++++*/
	$(document).ready(colorbox);
	$(window).on('resize', colorbox);

	function colorbox() {
		var baseWidth = $(window).width();
		var w = baseWidth * 0.8;
		var h = w * 0.57;
		$(".popChara").colorbox({
			maxWidth: "90%",
			rel:"img"
		})

	};
	/*+++++
	news
	+++++*/
	$(".newsInfo").colorbox({
		inline:true,
		maxWidth:"100%",
		maxHeight:false,
		opacity: 0.7,
		onOpen:function(){ current_scrollY = $( window ).scrollTop();
			$( '.wrapper' ).css( {
			  position: 'fixed',
			  width: '100%',
			  top: -1 * current_scrollY
			} ); },
			onClosed:function(){ $( '.wrapper' ).attr( { style: '' } );$( 'html, body' ).prop( { scrollTop: current_scrollY } ); }
	});


	$(".slideImgList").slick({
		infinite: true,
		slidesToShow: 1,
		slidesToScroll: 1,
		dots: false,
		prevArrow: '<img src="./assets/images/jp/common/arrow_l.png" width="100%" class="slide-arrow prev-arrow" >',
		nextArrow: '<img src="./assets/images/jp/common/arrow_r.png" width="100%"class="slide-arrow next-arrow" >',
		responsive: [{
				breakpoint: 600,
				settings: {
					slidesToShow: 1,
					slidesToScroll: 1,
				}
			}

		]
	});
	
	$('input[name="tabItem"]').change(function () { //tab切り替え時に画像サイズの再取得
		$(".slideImgList").slick('setPosition');
	});

	var pagetop = $('#pageTop');
    pagetop.hide();
    $(window).scroll(function () {
        if ($(this).scrollTop() > 100) { //100pxスクロールしたら表示
            pagetop.fadeIn();
        } else {
            pagetop.fadeOut();
        }
    });
    pagetop.click(function () {
        $('body,html').animate({
            scrollTop: 0
        }, 200); //0.5秒かけてトップへ移動
        return false;
    });

	/*+++++
	mobile menu
	+++++*/


	$(".openBtn").on("click",function(){
		var on = "is-on";
		$(".mobileNavBox").addClass(on)
	});
	$(".closeBtn").add(".mobileNav").on("click",function(){
		var on = "is-on";
		$(".mobileNavBox").removeClass(on)
	});

	$(".fadeIn").on('inview', function (event, visible) {
		if (visible == true) {
		$(this).addClass(on);
		}
	});
	
});