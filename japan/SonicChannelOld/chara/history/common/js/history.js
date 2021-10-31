/*SONIC CHANNEL Javascript 2006
--------------------------------------------------------------------------------
General page structure
------------------------------------------------------------------------------*/
//change bodyID
function bodyId(){
	if(pathArray[1].indexOf("html") != -1){
		idName = "topPage";
	}else{
		var idName = pathArray[3];
		if(pathArray[4].indexOf("html") == -1){
				idName += "-" + pathArray[4];
		}
	}

	var bodyObj = document.getElementsByTagName("body");
	bodyObj[0].id = idName;
	//alert(idName);
}
