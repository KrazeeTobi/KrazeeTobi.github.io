var imagenumber = 121;
var image_rand = Math.round((imagenumber-1) * Math.random()) + 1 ;
var titlepic = '<IMG SRC=/images/titlebar/pics/' + image_rand + '.gif align=left valign=middle>'

var logonumber = 44;
var logo_rand = Math.round((logonumber-1) * Math.random()) + 1;
var titlelogo = '<IMG SRC=/images/titlebar/logos/' + logo_rand + '.gif align=right valign=middle>';

	var num_menus = 11;
	var title = new Array;
	var link = new Array;
	var menutext = new Array;
	var menubarwidth = 620;

	title[0] = 'Sonic HQ';
	title[1] = 'News';
	title[2] = 'Games';
	title[3] = 'Comics';
	title[4] = 'Cartoons';
	title[5] = 'Music';
	title[6] = 'Downloads';
	title[7] = 'Fan Fair';
	title[8] = 'Q&A';
	title[9] = 'Forums';
	title[10] = 'Directory';
	link[0] = '/main.htm';
	link[1] = '/news/news.htm';
	link[2] = '/games/';
	link[3] = '/comics/';
	link[4] = '/cartoon/';
	link[5] = '/music/';
	link[6] = '/images/';
	link[7] = '/fanfair/';
	link[8] = '/qa/';
	link[9] = '/redirect.php/forum';
	link[10] = '/dir/';
// <br><LI><a href=/news/newslinks.htm>News Links</a>
// <br><LI><a href=/games/whoswho/>Profiles</a><br><LI><a href=/games/legends/legends.htm>History</a><br><LI><a href=/games/links.html>Links</a>
// <br><LI><a href=/comics/reviews/>Profiles</a><br><LI><a href=/comics/sonicgrams/>Special Links</a><br>
// <br><LI><a href=/cartoon/downloads.html>Cartoon Dowloads</a>
	menutext[0] = '</center><table width=115 border=1 bordercolorlight="blue" bordercolordark="#23238E"><tr><td><font size=2 face="Helvetica" color=white><LI><a href=/main/updateboard.htm>Update Board</a><br><LI><a href=/main/email.htm>Free E-Mail</a><br><LI><a href=/main/staff.php>Staff</a><br><LI><a href=/main/nostalgia/>Time Capsule</a><br><LI><a href=/main/awards.htm>Awards</a></td></tr></table>';
	menutext[1] = '<table width=115 border=1 bordercolorlight="orange" bordercolordark="#550000"><tr><td><font size=2 face="Helvetica" color=white><LI><a href=/news/archive.php3>Archive</a><br><LI><a href=/news/interviews.php3>Interviews</a><br><LI><a href=/news/editorials/>Editorials</a><br><LI><a href=/news/survey>Survey</a></td></tr></table>';
	menutext[2] = '<table width=115 border=1 bordercolorlight="purple" bordercolordark="#805500"><tr><td><font size=2 face="Helvetica" color=white><LI><a href=/games/index/>Game Index</a><br><LI><a href=/games/replay/>Replay Zone</a><br><LI><a href=/games/gameplay/>Gameplay</a><br><LI><a href=/games/neverwas/>Secrets</a></td></tr></table>';
	menutext[3] = '<table width=145 border=1 bordercolorlight="red" bordercolordark="#800055"><tr><td><font size=2 face="Helvetica" color=white><LI><a href=/comics/archive/>The Comics Archive</a><br><LI><a href=/comics/whoswho/>Previews<br><LI><a href=/comics/reviews/>Reviews<br><LI><a href=/comics/scans/>The Scans Archive</a></td></tr></table>';
	menutext[4] = '<table width=145 border=1 bordercolorlight="sky blue" bordercolordark="#23238E"><tr><td><font size=2 face="Helvetica" color=white><LI><a href=/cartoon/before/>Before SatAM</a><br><LI><a href=/cartoon/SatAM.php3>Sonic SatAM</a><br><LI><a href=/cartoon/AoStH.php3>Adventures Of STH</a><br><LI><a href=/cartoon/anime.php3>Sonic Anime OVA</a><br><LI><a href=/cartoon/SU.php3>Sonic Underground</a></td></tr></table>';
	menutext[5] = '<table width=145 border=1 bordercolorlight="green" bordercolordark="#550000"><tr><td><font size=2 face="Helvetica" color=white><LI><a href=/music/display.cgi?series=series>Browse By Series</a><br><LI><a href=/music/display.cgi>Browse By Platform</a><br><LI><a href=/music/updates/index.cgi>Browse by Update</a></td></tr></table>';
	menutext[6] = '<table width=200 border=1 bordercolorlight="red" bordercolordark="#805500"><tr><td><font size=2 face="Helvetica" color=white><LI><a href=/images/boxes/>Box Art & Music Covers</a><br><LI><a href=/images/screenshots/>Screenshots</a><br><LI><a href=/images/sprites/>Sprites</a><br><LI><a href=/images/chars/>Character Pictures & Images</a><br><LI><a href=/images/merchandise/>Sonic Merchandise</a><br><LI><a href=/images/articles/>Magazine Articles</a><br><LI><a href=/images/games.html>Videogame Demos</a><br><LI><a href=/images/downloads/movies.shtml>Movie Downloads</a></td></tr></table>';
	menutext[7] = '<table width=145 border=1 bordercolorlight="pink" bordercolordark="#800055"><tr><td><font size=2 face="Helvetica" color=white><LI><a href=/fanfair/edited/>Fanfair Hoaxes</a><br><LI><a href=/fanfair/fanart/>Fanfair Fan Art</a><br><LI><a href=/fanfair/fangames>Sonic Fan Games</a><br><LI><a href=/fanfair/fan-fic>Fan Fiction</a><br><LI><a href=/fanfair/fancomics>Fan Comics</a><br><LI><a href=/fanfair/comicstrips>Comic Strips</a></td></tr></table>';
	menutext[8] = '<table width=145 border=1 bordercolorlight="dark blue" bordercolordark="#23238E"><tr><td><font size=2 face="Helvetica" color=white><LI><a href=/qa/>Question & Answer</a><br><LI><a href=/qa/FAQ.htm>The Sonic FAQ File</a></td></tr></table>';
	//<LI><a href=http://pub12.ezboard.com/fsonichqcommunityfrm22>The Kobun Kiosk (Guestbook)</a><LI><a href=http://pub12.ezboard.com/fsonichqcommunityfrm11>The Emerald Chatstation (SHQ)</a><br><LI><a href=http://pub12.ezboard.com/fsonichqcommunitymobiusforum>The Mobius Forum (General)</a><br><LI><a href=http://pub12.ezboard.com/fsonichqcommunityfrm21>The Ladies Lounge</a><br><LI><a href=http://pub12.ezboard.com/fsonichqcommunityfrm18>Special Zone (Sonic The Comic UK)</a><br><LI><a href=http://pub12.ezboard.com/fsonichqcommunityfrm10>South Island (Segasonic)</a><br><LI><a href=http://pub12.ezboard.com/fsonichqcommunityfrm8>Knothole Village (Archie Sonic)</a><br><LI><a href=http://pub12.ezboard.com/fsonichqcommunityfrm9>The Floating Island (Knuckles Fans)</a><br><LI><a href=http://pub12.ezboard.com/fsonichqcommunityfrm14>The Robot Museum (MMHQ)</a><br><LI><a href=http://pub12.ezboard.com/fsonichqcommunitystationsquarenewsandeditorials>Station Square (News & Editorials)</a><br><LI><a href=http://pub12.ezboard.com/fsonichqcommunitycarnivalislefanfictionfanprojects>Carnival Island (Fan Fiction)</a><br><LI><a href=a href=http://pub12.ezboard.com/fsonichqcommunitythetradingpost>Nacks Trading Post (Sonic Trade)</a><br><LI><a href=http://pub12.ezboard.com/fsonichqcommunitysonicroleplay>The Role Players Guild</a>
	menutext[9] = '<table width=235 border=1 bordercolorlight="yellow" bordercolordark="#550000"><tr><td><font size=2 face="Helvetica" color=white><LI><a href=aim:gochat?roomname=Sonic+HQ+Emerald+Chat>HQ Chat Room (Requires AIM)</a></td></tr></table>';
	menutext[10] = '<table width=140 border=1 bordercolorlight="dark purple" bordercolordark="#805500"><tr><td><font size=2 face="Helvetica" color=white><LI><a href=/dir/directory.php3/dir/106>Sonic Links</a><br><LI><a href=/dir/top10.php>Top 10 Links</a><br><LI><a href=/dir/unique.php>Unique Sonic Links</a><br><LI><a href=/dir/developer.php>Official Developers</a><br><LI><a href=/dir/webrings.htm>Webrings</a><br><LI><a href=/dir/sonic_oscar.htm>The HQ Award</a></td></tr></table>';

function MidiPlayer () {
midiplayer = window.open("", "MidiPlayer", "toolbar=no,location=no,directories=no,status=no,menubar=no,scrollbars=no,width=200,height=60")
midiplayer.document.open();
midiplayer.document.write('<html><title>Midi Player</title><base href=http://www.sonichq.org/><body LEFTMARGIN=0 TOPMARGIN=0 MARGINHEIGHT=0 MARGINWIDTH=0><embed src=' + midi + ' autostart=true width=200 height=60 loop=true><br><center>' + caption + '</center></html>');
midiplayer.document.close();
}

var theme = "main";
var midis = new Array;
var captions = new Array;

	var i = 1;

	midis[i]="http://www.geocities.com/EnchantedForest/Tower/4309/mm8Tengu.mid"
	captions[i]="Tengu Man (Saturn) by Maelgrim"
	midis[++i]="http://www.geocities.com/EnchantedForest/Glade/8862/Gravityman.mid"
	captions[i]="Gravity Man Echo Remix by Maelgrim"
	midis[++i]="music/midis/sonic/1/s1starlightjr.mid"
	captions[i]="Star Light Zone by Jeff Read "
	midis[++i]="music/midis/sonic/1/s1starlightjw.mid"
	captions[i]="Star Light Zone by John Weeks"
	midis[++i]="music/midis/sonic/1/s1starlightr.mid"
	captions[i]="Star Light Zone by Riwo"

	var space=i;

	midis[++i]="http://www.geocities.com/EnchantedForest/Dell/7835/ricecapdb.mid"
	captions[i]="Ice Cap Epic by David Bulmer"
	midis[++i]="http://www.geocities.com/EnchantedForest/Dell/6657/Take_the_Snow_Train.mid"
	captions[i]="Nights Into Dreams: Take the Snow Train!"
	midis[++i]="games/rnf-cold.mid"
	captions[i]="Cold Man's Stage by Maelgrim"
	midis[++i]="http://www.geocities.com/EnchantedForest/Dell/7835/ricecapwa.mid"
	captions[i]="Ice Cap Wild by Wild Alpha"
	midis[++i]="http://www.geocities.com/EnchantedForest/Dell/7835/ESAMetropolistrancezone.mid"
	captions[i]="Metropolis Trance Zone by Edan Koch"
	midis[++i]="music/midis/sonic/3dblast/diamonddust-act2-jw.mid"
	captions[i]="Diamond Dust Zone Act 2 Genesis by John Weeks"

	var ice=i;

	midis[++i]="music/midis/sonic/s1g/gs1bridgejr.mid"
	captions[i]="Bridge Zone (Version 1) by John Weeks"

	var tails=i;

	midis[++i]="http://www.geocities.com/EnchantedForest/Dell/7835/kcasolatedislandk3.mid"
	captions[i]="Door Into Summer (Isolated Island Zone) (Version 3) by Koryan"
	midis[++i]="music/midis/sonic/chaotix/kcbotonicbasek3.mid"
	captions[i]="Midnight Greenhouse (Botanic Base Zone) (Version 3) by Koryan"

	var espio=i;

	midis[++i]="music/midis/sonic/3dblast/rustyruin-act2-jw.mid"
	captions[i]="Rusty Ruin Zone Act 2 Genesis by John Weeks"
	midis[++i]="music/midis/mm/x3/GravityBeetle-jj.mid"
	captions[i]="Gravity Beetle's Stage by Jarel Jones"

	var e102=i;

	midis[++i]="/music/midis/sonic/3k/flyingbattery2-k.mid"
	captions[i]="Flying Battery Act 1 by Koryan"
	midis[++i]="http://www.geocities.com/enchantedforest/dell/7835/skcflyingbattery.mid"
	captions[i]="Flying Battery Act 1 by SEGA"
	midis[++i]="music/midis/sonic/3dcd/panicpuppetjr.mid"
	captions[i]="Panic Puppet Zone Act 1 by Jeff Read"

	var metalsonic=i;

	midis[++i]="music/midis/sonic/chaotix/kcspeedsliderk2.mid"
	captions[i]="Speed of Sound (Speed Slider Zone) (Version 2) by Koryan"
	midis[++i]="http://www.geocities.com/EnchantedForest/Dell/7835/s3creditsek3.mid"
	captions[i]="Sonic 3 Credits Mix 3 by Edan Koch"
	midis[++i]="http://www.geocities.com/EnchantedForest/Dell/7835/skcskysanctuary.mid"
	captions[i]="Sky Sanctuary Zone by SEGA"
	midis[++i]="http://www.geocities.com/EnchantedForest/Dell/7835/SE.mid"
	captions[i]="Sonic Electronic by Jeff Read"
	midis[++i]="http://www.geocities.com/EnchantedForest/Dell/7835/KR.mid"
	captions[i]="King of the Ring (Radio Zone) by Jeff Read"
	midis[++i]="music/midis/south-island.mid"
	captions[i]="South Island"

var nummidis = i;
day = new Date()
seed = day.getTime()
ran = parseInt(((seed - (parseInt(seed/1000,10) * 1000))/10)/100*nummidis + 1,10)

var midi = midis[ran];
var caption = captions[ran];

if(ran <= space) theme = "space";
else if(ran <= ice) theme = "ice";
else if(ran <= tails) theme = "tails";
else if(ran <= espio) theme = "espio";
else if(ran <= e102) theme = "e102";