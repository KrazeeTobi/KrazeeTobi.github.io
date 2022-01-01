// JavaScript Document
$(function(){
	$("ol").each(function(){
		jQuery(this).find("li:even").addClass("liEven");
	});
});