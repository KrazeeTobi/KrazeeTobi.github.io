<!DOCTYPE html>
<html>
  <head>
    <title>Start</title>
    <meta http-equiv="X-UA-Compatible" content="IE=edge"/>
    <meta http-equiv="content-type" content="text/html; charset=utf-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <meta name="apple-mobile-web-app-capable" content="yes"/>
    <link href="./nonAuth/axure_rp_page.css" type="text/css" rel="stylesheet"/>
    <link href="./nonAuth/BTstyles.css" type="text/css" rel="stylesheet">
    <link href="./nonAuth/m_hurl.css" type="text/css" rel="stylesheet">
    <link href="./nonAuth/BTfont.css" type="text/css" rel="stylesheet">
    <link rel="shortcut icon" href="../images/favicon1.ico" type="image/x-icon">
	<link rel="icon" href="../images/favicon1.ico" type="image/x-icon">
    <script src="./nonAuth/jquery-1.7.1.min.js"></script>
    <script src="./nonAuth/jquery-ui-1.8.12.custom.min.js"></script>
    <script language="JavaScript" type="text/javascript">
    	var CGIs = [];
    </script>
    <script src="./nonAuth/globals.js"></script>
    <script src="./nonAuth/Hurl.js"></script>

    <script language="javascript"  type="text/javascript">

	var device_version = 0;
	function init(){
		pm_init();

		/*PC: device_version=0, mobile: device_version > 0*/
		if(device_version == 0){
			var ToppestMenu;
			ToppestMenu = ShowHurlTopMenu();
			document.getElementById("Hurl_toppest").innerHTML = ToppestMenu;

			setHurlInputBtn("start_troubleshooting", "hurl_sys.htm#001", "Start troubleshooting");
			
		}else{
			var ToppestMenu;
			ToppestMenu = m_ShowHurlTopMenu();
			document.getElementById("m_Hurl_toppest").innerHTML = ToppestMenu;
			if(device_version == 1){
				m_setHurlInputBtn("m_start_troubleshooting", "hurl_sys.htm#001", "Start troubleshooting");
			}else if(device_version == 2){
				m_setHurlInputBtn("m_start_troubleshooting", "hurl_sys.htm#001", "Start troubleshooting");
			}
		}
    	}
	
    	
    </script>
  </head>

  <body onLoad="init()">
  <FORM name="tF0" action="./cgi-bin/statusprocess.exe" method="post" target="OUTfrm">
  	 <div id="base" style="display:none;" class="">
  	 	<!--TopMenu-->
	    	<div id="Hurl_toppest">
	    	</div>

	    	<span class="EEtitleFont_hurl" style="position:absolute; top:80px; width:270px;">Unable to connect to the Internet</span>
	    	<img alt="" style="position:absolute; top:113px; left:205px;"  src="../images/hurl_hub.png"/>
	    	<img alt="" style="position:absolute; top:272px; left:545px;"  src="../images/hurl_alert.png"/>
	    	
	    	<span class="EEregularFont_hurl" style="position:absolute; top:330px; width:500px;">
	    		Your EE Smart Hub has detected a problem with your internet connection.
	    		<br><br>
	    		We'll now take you through some simple steps to try to fix things.
	    	</span>
	    	
	    	<img alt="" style="position:absolute; top:400px; width:720px; height:2px;"  src="../images/sub_menu_line_u677_line.png"/>
	    	<label id="start_troubleshooting" style="position:absolute; top:420px; left:260px;"></label>
  	 </div>

  	 <div id = "mobile" style="display:none;" class="mobile_width">
  	 	<!--TopMenu-->
	    	<div id="m_Hurl_toppest">
	    	</div>

	    	<span class="m_titleFont mobile_font_size2 colorGray" style="position:absolute; top:60px; width:270px; left:10px;">Unable to connect to the Internet</span>
	    	<img alt="" style="position:absolute; top:95px; left:30px; width:255px; height:170px;"  src="../images/hurl_hub.png"/>
	    	<img alt="" style="position:absolute; top:225px; left:265px;"  src="../images/hurl_alert.png"/>
	    	<div class="mobile_Swidth" style="position:absolute; top:275px;">
		    	<span class="m_regularFont mobile_Swidth mobile_font_size2 colorGray" style="position:relative; left:10px;">
		    		Your EE Smart Hub has detected a problem with your internet connection.
		    		<br><br>
		    		We'll now take you through some simple steps to try to fix things.
		    	</span>
		    	<img alt="" class="mobile_Swidth" style="position:relative; top:0px; left:10px; height:2px;"  src="../images/sub_menu_line_u677_line.png"/>
		    	<label id="m_start_troubleshooting" class="hurlBtnLeft1" style="position:relative; top:10px;"></label>
	    	</div>
  	 </div>
  </FORM>
  </body>
</html>
