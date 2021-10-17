$(function(){
/*
<h3><div class="h3Wrap"><tmp name="topics_title" /></div></h3>
<h4><tmp name="title" /><span class="topicsDate"><tmp name="lastdate" /></span><span class="newInfo"><tmp name="mark_new" /></span></h4>
<div class="contensSubstance">
	<div class="divWrap">
		<tmp name="text" />
	</div>
</div>
*/
$(document).ready(function() {
	var $topics_all = $('#common-contents > article');
	
	var xmlFile = 'topics.xml';
	$.ajax({
		url: xmlFile
		,type: 'GET'
		,dataType:"xml"
		,cache: false
		,error: function() {
			try {
				var xmlDom = new ActiveXObject("Microsoft.XMLDOM");
				xmlDom.onreadystatechange = function() {
					topicsCreate(xmlDom);
				}
				xmlDom.load(xmlFile);
			} catch(e) {
				$topics_all.append(e);
				//Eroor
			}
		}
		,success: function(xml){
			topicsCreate(xml);
		}
	}); 

	function topicsCreate(xml){
		$('topics',xml).each(function(){
			var $topics = $(this);
			$topics_all.append('<h3 id="contents-topics0'+($topics.index()+1)+'"><div class="h3Wrap">'+ $topics.attr("title") +'</div></h3>');
			$('item',$topics).each(function(){
				var $item = $(this);
				var mark_new = '';
				if($item.find('mark_new').text() == "true"){
					mark_new = '<span class="newInfo"><tmp name="mark_new" /></span>';
				}
				var file_name = $topics.attr("name") + '-' + $item.find("name").text();
				$topics_all.append('<h4 class="close" data="'+ file_name +'.html">'+$item.find('title').text()+'<span class="topicsDate"><tmp name="lastdate" />'+$item.find('lastdate').text()+'</span>'+mark_new+'</h4>');
				$topics_all.append('<div class="contensSubstance" id="'+ file_name +'"></div>');
				
			});
			
		});
		var accordion = $('.bodyTopics').accordionMove({read:true});
	}

});
});