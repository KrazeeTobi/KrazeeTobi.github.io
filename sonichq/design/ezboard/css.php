<!doctype html public "-//w3c//dtd html 4.0 transitional//en">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<title>Design HQ</title>
<LINK REL="SHORTCUT ICON" HREF="favicon.ico">
<style type="text/css">
<!-- a:hover {text-decoration: underline}
A{text-decoration:none} -->
</style>
<script src=/sonichq/scripts/sonic-init.js></script>
<script language=JavaScript>
<!--
document.write('<link rel=stylesheet href=/sonichq/css/' + theme + '.css type="text/css">')
//-->
</script>
<noscript>
<link rel=stylesheet href=/sonichq/css/main.css type="text/css">
</noscript>
</head>

<body text="#000000" bgcolor="white" link=3366ff vlink=3366ff background="/sonichq/images/backgrounds/TailsGrayBG.gif" bgproperties="fixed">

<br>

<center>
<!-- Place the following code where you want an ad to appear -->
<IFRAME SRC="https://web.archive.org/20011211000000/http://ads.ad-flow.com/?DC=ztnet-ron-top&DH=Y&TARGET=_blank" HEIGHT="60" WIDTH="468" SCROLLING="NO" MARGINWIDTH="0" MARGINHEIGHT="0" FRAMEBORDER="0" VSPACE="0" HSPACE="0">
<ILAYER SRC="https://web.archive.org/20011211000000/http://ads.ad-flow.com/?DC=ztnet-ron-top&TARGET=_blank&DH=Y" HEIGHT="60" WIDTH="468">
</ILAYER>
<NOLAYER>
<A HREF="https://web.archive.org/20011211000000/http://ads.ad-flow.com/?SHT=ztnet-ron-top" TARGET="_blank"><IMG SRC="https://web.archive.org/20011211000000/http://ads.ad-flow.com/?SIT=ztnet-ron-top" HEIGHT="60" WIDTH="468"></A>
</NOLAYER>
</IFRAME></center>

<p><span class=pathlinks><table class=glow>
<a href=/sonichq/design>Design HQ</a> | <a href=/sonichq/design/ezboard>EZBoard Customization</a> | Style Sheets For Admins</table></span>

<center>

<!main table top>
<p><table BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH="100%" class=maintable>
<tr><td width=19><img src=/sonichq/topleft.gif width=19></td>

<td bgcolor=black width=100% height=50>
<script language=JavaScript>
<!--
document.write(titlepic + titlelogo)
//-->
</script>
&nbsp;</td>

<td width=19><img src=/sonichq/topright.gif width=19></td></tr>
</table>
<!end main table top>

<table BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=100% class=maintable><td valign=middle width=100% bgcolor=black><font size=2>
<script src=/sonichq/scripts/menu.js></script>
<noscript>&nbsp;</noscript>
</font></td></table>

<!main table middle>
<table BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=100% class=maintable><tr>

<td VALIGN=TOP WIDTH="70%" bgcolor=ffffff class=itemtable>
<font face=Arial size=2 class=itemtable>

<!sections>
<div class=titlebar><table class=glow>
<a name="NonUnderlinedLinks">Non-Underlined Links</a>
</table></div>

<div class=itemtext>
In this code, links only have underlines when the mouse is over them.<p><textarea rows=10 cols=40><style>
a {text-decoration:none;}
a:hover {text-decoration:underline;}
</style></textarea><p>
</div><div class=titlebar><table class=glow>
<a name="ColoredScrollbars">Colored Scrollbars</a>
</table></div>

<div class=itemtext>
Colored scrollbars require IE 5.5+.  The colors are, of course, customizable.
<p><textarea rows=10 cols=40><style>
BODY {
scrollbar-face-color: #000055;
scrollbar-shadow-color: black; 
scrollbar-highlight-color: white;
scrollbar-3dlight-color: blue;
scrollbar-darkshadow-color: #00002B;
scrollbar-track-color: white;
scrollbar-arrow-color: #B0FFFF
}
</style></textarea><p>
</div><div class=titlebar><table class=glow>
<a name="GlowingText">Glowing Text</a>
</table></div>

<div class=itemtext>
To make individual text glow, use this technique.  The default color is red, and both the glow size and color are customizable.<p><textarea rows=2 cols=40><table style="filter:GLOW(color=blue, strength=#+7);"><td>Your Text Here</td></table></textarea><p>However, if you use this effect frequently on your board, it's better to make a style for it in your header.<p><textarea rows=5 cols=40><style>
<!--
.glow {filter:GLOW(color=blue, strength=#+7);}
-->
</style></textarea><p>Use this simpler code on the text you want to glow.  This will also let you change the color of all your glowing text by setting the color for your entire board in the header.  This won't affect glowing text that uses the first method, though.<p><textarea rows=2 cols=40><table class=glow><td>Your Text Here</td></table></textarea><p>
</div><div class=titlebar><table class=glow>
<a name="ButtonStyles">Custom Buttons And Combo Boxes</a>
</table></div>

<div class=itemtext>
To see this code in-browser, click  <a href=https://web.archive.org/20011211000000/http://pub12.ezboard.com/bsonichqcommunity>here</a>.  This code customizes buttons, checkboxes, and the drop-box menus used for EZRings and the Jump To Forum box.  "Input" contains properties for the buttons and checkboxes, and "select"  contains properties for the combo boxes.<p>"Color", "font-family", and "font-size" control text, "background-color" controls the colors of the buttons and boxes themselves, "vertical-align:middle" vertically centers the text on the buttons and boxes, "margin-left" puts space between the buttons and the boxes on the EZRing and Jump To Forum menus, and the border settings put a shaded border around the buttons.<p><textarea rows=10 cols=40><style>
input {
color:#ffffff;
font-family:verdana,arial,helvetica,sans-serif;
font-size:8pt;
margin-left:2;
vertical-align:middle;
background-color:#000000;
border-left:3 solid white;
border-top:3 solid white;
border-bottom:3 solid black;
border-right:3 solid black;
}
select {
color:#ffffff;
font-family:verdana,arial,helvetica,sans-serif;
font-size:10pt;
vertical-align:middle;
background-color:#000000;
}
textarea {
font-family:verdana,arial,helvetica,sans-serif;font-size:10pt;color:#ffffff;background-color:#000000;
}
</style></textarea><p>
</div><!end of sections>

</td>

<!black side bar>
<td width=4>&nbsp;</td>
<td valign=top bgcolor=000000 class=sidebar><font face=Arial size=-1 color=white><br>

<script language=JavaScript>
<!--
document.write('<center>MIDI: ' + caption + '<br><a href="#" onClick="MidiPlayer();return false;">Start Midi</a></center><br>')
//-->
</script>

<u>Style Sheets For Admins</u><p>Styles generally take effect on page elements that ppear below them on the page, so you should probably put most styles in your custom header unless otherwise noted.
<p><center><IFRAME SRC="https://web.archive.org/20011211000000/http://ads1.ad-flow.com/?DC=ztnet-ron-rst&TARGET=_blank" HEIGHT="125" WIDTH="125" SCROLLING="NO" MARGINWIDTH="0" MARGINHEIGHT="0" FRAMEBORDER="0" VSPACE="0" HSPACE="0">
<SCRIPT LANGUAGE="JavaScript">document.write('<SCR'+'IPT LANGUAGE="JavaScript" SRC="https://web.archive.org/20011211000000/http://ads1.ad-flow.com/?DC=ztnet-ron-rst&JS=Y&TARGET=_blank"></SCR'+'IPT>');</SCRIPT>
<NOSCRIPT>
<A HREF="https://web.archive.org/20011211000000/http://ads1.ad-flow.com/?SHT=ztnet-ron-rst" TARGET="_blank"><IMG SRC="https://web.archive.org/20011211000000/http://ads1.ad-flow.com/?SIT=ztnet-ron-rst" HEIGHT="125" WIDTH="125"></A>
</NOSCRIPT>
</IFRAME>
</center>

</font></td></tr>
</table>
<!end main table middle>

<!main table bottom>
<table border=0 cellspacing=0 cellpadding=0 width=100% class=maintable><tr>
<td><img SRC="/sonichq/bottomleft.gif" BORDER=0 height=20></td>
<td width=99% bgcolor=000000><font color="white" size=-3 face="arial"><center>Page is ©1996-2001 Sonic HQ.  Sonic & Co. are © Sega.</center></font></td>
<td><img SRC="/sonichq/bottomright.gif" BORDER=0 height=20></td>
</tr></table>
<!end main table bottom>

</center>
</body>
</html>
