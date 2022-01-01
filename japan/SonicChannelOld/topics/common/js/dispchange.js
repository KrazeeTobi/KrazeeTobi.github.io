function dispChange(num,maxNum){
	for(i=1;i<=maxNum; i++){
		var id = "pic" + i;
		if(i==num){
			if(document.all){
				document.all(id).style.display = "block";
			}else if(document.getElementById){
				document.getElementById(id).style.display = "block";
			}
		}else{
			if(document.all){
				document.all(id).style.display = "none";
			}else if(document.getElementById){
				document.getElementById(id).style.display = "none";
			}
		}
	}
}