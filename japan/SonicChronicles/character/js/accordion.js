// JavaScript Document

$(document).ready(function() {
	$("#contents dd").css("display","none");
	var contArr = new Array();
	$("#contents-substance").children().each(function(){
		if($(this).get(0).tagName == "DIV"){
			contArr.push($(this));
			$(this).css("display","none");
		}
	});

	$("#contents-navigation ul li a").each(function(){
		$(this).attr("href","#");
	});
	
	contArr[0].css("display","block");

	//ナビがクリックされた時
	$("#contents-navigation ul li a").click(function(){
		var selectBtn = $(this).parent().attr("id").split("-");
	 	for(i=0;i<contArr.length;i++){
			var contID = contArr[i].attr("id").split("-");
			if(contID[1] == selectBtn[1]){
				if(contArr[i].css("display")=="none"){
					contArr[i].slideDown(500);
				}
			}else{
				if(contArr[i].css("display")!="none"){
					contArr[i].slideUp(1000);
				}
			}
				
		}
	});
	
});	

