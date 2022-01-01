// JavaScript Document
//	var latestNo=0; // latestNoAjaxから読み込んだ値を格納


	var liAmount=0;           //総数
	var currentPageTopLi=0;     //現在ページ中の先頭liのindex
//	var currentPageEndLi=0;     //現在ページ中の最後liのindex
	var liIndex=0;            //先頭からのindex
	
	var currentPage=1;
	var totalPage=0;


$(document).ready(function(){

	/*------------------------------------------------------------
	初期化
	------------------------------------------------------------*/

	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* 
		プロパティファイル読込
	*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	function latestNoAjax(){
		var defNo =-1;
		$.ajax({
			url:'data/latestNo.txt',
			dataType: 'text'
		})
		.done(function(data){
				var data_array = data.split(/\r\n|\r|\n/);
				defNo = parseInt(data_array[0],10);
				if(isNaN(defNo) || parseInt(data_array[0],10)<=0 || parseInt(data_array[0],10)>39){
					defNo = 1;
				}else{
					defNo = parseInt(data_array[0],10);
				}
				contentAjax(defNo);
		})
		.fail(function(){
				alert('txt 問題がありました。');
		});

	}//--- END latestNoAjax()---------
	

	$('article.contentsKnowledge:not(:animated)').animate({opacity:1},100); //あとで追加

	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* 
		コンテンツ読込
	*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	function contentAjax(no){
		
		$('article.contentsKnowledge').empty().hide();
		if(no<10){//1桁だった場合の0パディング
			no=('00' + no).slice(-2);
		}
		var fileURL ='data/miniInfoData/miniInfo_'+no+'.html';
		
		$.ajax({
						type: 'GET',
						url: fileURL,
						dataType: 'html'
		})
		.done(function(data){
			$('article.contentsKnowledge').append(data).fadeIn(500);
			
		})
		.fail(function(){
			alert('contentAjax 問題がありました。');
		});
		
	}
	
	function dispLinkPrevNext(){
		// 【prev】【next】ボタンの表示切替処理
		$('nav#common-navigation #prev').removeClass("disp");
		$('nav#common-navigation #next').removeClass("disp");
		if(currentPage>1) $('nav#common-navigation #prev').addClass("disp");
		if(currentPage<totalPage) $('nav#common-navigation #next').addClass("disp");
	}
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* 
		navi読込
	*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	function naviAjax(){
		$.ajax({
						type: 'GET',
						url: 'data/navi.html',
						dataType: 'html'
		})
		.done(function(data){
			$('nav#common-navigation ul').append(data);
			$('nav#common-navigation ul li').click(
				function(){
					var index = $(this).attr("id").replace("rel-","");
					$.when($('article.contentsKnowledge').fadeOut(300))
					.done(function(){contentAjax(index);});
					
					//contentAjax(index);
					/**/
					return false;
				}
			);
			/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
			 dispクラスをli先頭8個にaddClass
			-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
			liAmount = $('#common-navigation ul li').length;// li総数
			totalPage = Math.ceil(liAmount/8);

			$('#common-navigation ul li').each(function(index) {
				//ページが読込まれた時だけ実行されるはず(1度だけ)
				if(index<8){
					if(index==0) {
						currentPageTopLi =0;
						$('nav#common-navigation #prev').removeClass("disp");
					}
					
					// 【prev】【next】ボタンの表示切替
					if(liAmount<=8 && liAmount-1==index){ //--------------li総数が1ページ未満の場合
						//currentPageEndLi=index;
						$('nav#common-navigation #next').removeClass("disp");
					}else{ //---------------------------------------------li総数が2ページ以上の場合   
						//currentPageEndLi=7;
						$('nav#common-navigation #next').addClass("disp");
					}
					
					$(this).addClass("disp");
				}else{
					$(this).removeClass("disp");
				}
			});
			
			
			/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
			/* prev next ボタンイベント処理 */
			$('nav#common-navigation #prev').click(function(){
				$('#common-navigation ul li').removeClass("disp");
				currentPageTopLi = currentPageTopLi+1;

				if(currentPage != 1){currentPage = currentPage-1;}
				var startLi = currentPage*8-8;
				$('#common-navigation ul li').each(function(index){
					// addClass disp
					if(startLi<= index &&  index < startLi+8) $(this).addClass("disp");
				});
				dispLinkPrevNext();
				return false;
			});
			
			$('nav#common-navigation #next').click(function(){
				$('#common-navigation ul li').removeClass("disp");
				
				var startLi = currentPage*8;
				$('#common-navigation ul li').each(function(index){
					if(startLi<= index &&  index < startLi+8) $(this).addClass("disp");
				}); 

				if(currentPage != totalPage){
					++currentPage;
				}
				dispLinkPrevNext();
				return false;
			});
			
			
		})
		.fail(function(){
			alert('navi読込 問題がありました。');
		})
	}//---END-- function naviAjax(){----------
	
	naviAjax();
	latestNoAjax();
	
		/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
		// 一時保留 かわりにwhenを使用
		*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
		/*
		$.when(latestNoAjax("★latestNoAjax引数★")).done(function(){
			//alert("when done関数　latestNo "+latestNo);
			contentAjax(latestNo);
		});
		*/
		/*★★★★★★★最終★★★★★★★★★★201411111507
		多分途中でグローバル変数latestNoがみれなくなってる
		latestNoを参照する方法、クラスにするとか。
		*/
});//---END --$(document).ready(function(){----------