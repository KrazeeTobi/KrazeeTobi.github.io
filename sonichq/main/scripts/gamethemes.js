<!--
// titlecolor is the color of title bars on the ppage
// tablebg is the background of tables on the page (could be no change, a color, or a graphic)

// Defaults
var biglogo = "../images/logos/games/spazfan.jpg"

var textcolor = "000000"
var linkcolor = "cyan"
var titlecolor = "404fe0"
var bordersettings = "cellspacing=0 bordercolorlight=blue bordercolordark=23238E"
var bg = "../images/backgrounds/TailsGrayBG.gif"
var tablebg = ""
var skip_titlebar = false

var maintable_start = "<table width=90% border=0 cellspacing=0 cellpadding=0><tr><td bgcolor=c0c0c0>&nbsp; "

var maintable_end = "<td bgcolor=c0c0c0>&nbsp;</table> "

if(theme == 1)
{
	// Space Settings
	textcolor = "3366FF"
	linkcolor = "ffffff"
	titlecolor = "333399"
	bg = "../images/backgrounds/starbkgr.jpg"
	tablebg = "bgcolor=000000"
	maintable_start = "<table width=90% bgcolor=000000 border=1 cellspacing=0 bordercolorlight=blue bordercolordark=23238E><tr>"
	maintable_end = "</tr></table>"
	skip_titlebar = true
}

if(theme == 2)
{
	// Ice Settings
	textcolor = "ffffff"
	titlecolor = "404fe0"
	bg = "../images/backgrounds/BlueCubism.gif"
	tablebg = "background=../images/backgrounds/bluecubism-dark.gif"
}

if(theme == 3)
{
	// Forest Settings
	textcolor = "ffffff"
	titlecolor = "green"
	bordersettings= "bordercolorlight=green bordercolordark=#green"
	bg = "../images/backgrounds/forest1.gif"
	//bg = "../images/backgrounds/knotholebigfade.jpg"
	tablebg = "background=../images/backgrounds/negaback3.jpg"
}
// -->