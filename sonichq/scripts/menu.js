// Menu program designed by J LaZor for use ONLY on Sonic HQ Network and SonicNEXT
ie=0; n=0; ns5=0;
ie = (document.all)? true:false
n = (document.layers)? true:false

bName = navigator.appName;
bVer = parseInt(navigator.appVersion);
if(bName == 'Netscape' && bVer >= 5) ns5=1;

if (num_menus) {}
else{
	//var num_menus = 1;
	//var title = new Array;
	//var link = new Array;
	//var menutext = new Array;
	//var menubarwidth = 577;

	//title[0] = 'Sonic HQ';
	//link[0] = '/';
	//menutext[0] = '<a href=/main.htm>Main Page</a>';
}

function showmenu(number) {
		if (ie) {document.all['pull' + number].style.visibility = "visible";}
}

function hidemenus(number) {
		var i;
		if (ie) {
			for(i=0; i<num_menus; i++) {
				if(i != number) {document.all['pull' + i].style.visibility = "hidden";}
			}
		}
}

function makemenus () {
	document.write('<div');
	if (n) {
		document.write(' style="layer-background-color:black;font-size:9pt;font-family:arial;color:white;');
	}
	else {
		document.write(' class=menu style="width:' + menubarwidth + ';');
	}
	document.write('position:relative;valign:middle;padding:4 0 4 0;">');
	for(i=0; i<num_menus; i++) {
		document.write('| ');
		if (ie) {
			document.write('<div class=menu ID=pull' + i + ' onmouseover="hidemenus(' + i + ');showmenu(' + i + ');" onmouseout="hidemenus();" style="position:absolute;visibility:hidden;visibility:hide;width:100;top:20;">' + menutext[i] + '</div>');
		}
		document.write('<a class=menu ID=menu' + i + ' href=' + link[i] + ' onmouseover="hidemenus(' + i + ');showmenu(' + i + ');">' + title[i] + '</a> ');
	}
	document.write('|</div>');
}

makemenus();
hidemenus();