var imagenumber = 9;
var image_rand = Math.round((imagenumber-1) * Math.random()) + 1 ;
var titlepic = '<IMG SRC=/megaman/images/titlebar/' + image_rand + '.gif align=left valign=middle>'

var logonumber = 23;
var logo_rand = Math.round((logonumber-1) * Math.random()) + 1;
var titlelogo = '<IMG SRC=/megaman/images/titlebar/logo1.gif align=right valign=middle>';

	var num_menus = 8;
	var title = new Array;
	var link = new Array;
	var menutext = new Array;
	var menubarwidth = 577;

	title[0] = 'Mega Man HQ';
	title[1] = 'News';
	title[2] = 'Games';
	title[3] = 'Music';
	title[4] = 'Fan Fair';
	title[5] = 'Multimedia';
	title[6] = 'Forum';
	title[7] = 'Directory';
	link[0] = '/megaman/';
	link[1] = '/news/megamannews.htm';
	link[2] = '/megaman/games/';
	link[3] = '/megaman/music.php3';
	link[4] = '/megaman/fanfair/';
	link[5] = '/megaman/images/';
	link[6] = 'http://pub12.ezboard.com/fsonichqcommunityfrm14';
	link[7] = '/megaman/directory.php3';
	menutext[0] = '<a href=/megaman/features/updateboard.htm>Update Board</a><br><a href=/megaman/features/staff.php3>Staff</a><br><a href=/megaman/features/nostalgia.php3>Time Capsule</a>';
	menutext[1] = '';
	menutext[2] = '<a href=/megaman/games>Game Index</a><br><a href=/megaman/games/replay.php3>Replay Zone</a><br><a href=/megaman/database/megaman/rockman&forte/>Robot Database</a>';
	menutext[3] = '<a href=/music/display.cgi?series=series&style=mm>Game Series</a><br><a href=/music/display.cgi?style=mm>Platforms</a><br><a href=/music/updates/index.cgi?style=mm>Updates</a>';
	menutext[4] = '<a href=/megaman/fanfair/edited/>Hoaxes</a><br><a href=/megaman/fanfair/fanart/>Fan Art</a><br><a href=/megaman/fanfair/fangames.php3>Fan Games</a><br><a href=/megaman/fanfair/fancomics>Fan Comics</a>';
	menutext[5] = '<a href=/megaman/images/boxcovers>Box Art</a><br><a href=/megaman/images/screenshots>Screenshots</a><br><a href=/megaman/images/proart>Character Art</a><br><a href=/megaman/images/sprites>Sprites</a><br><a href=/megaman/images/merchandise>Merchandise Pics</a><br><a href=/megaman/images/manga>Rockman Manga</a>';
	menutext[6] = '';
	menutext[7] = '<a href=http://www.ibis-research.com/MM/ target=_blank>Mega Man Home Page</a><br><a href=http://www.protoman.com/ target=_blank>The Protoman Homepage</a><br><a href=http://members.tripod.com/~Maelgrim/Rockman.html target=_blank>Rockman\'s World</a><br><a href=http://www.rockmanrobotcentre.8m.com/ target=_blank>Auto\'s Rockman Robot Centre</a><br><a href=http://www.kontek.net/m3a/ target=_blank>M3A - Mega Man MOD Archives</a>';

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
	midis[++i]="music/midis/mm/x3/GravityBeetle-jj.mid"
	captions[i]="Gravity Beetle's Stage by Jarel Jones"
	midis[++i]="music/midis/sonic/1/s1starlightjr.mid"
	captions[i]="Star Light Zone by Jeff Read "
	midis[++i]="music/midis/sonic/1/s1starlightjw.mid"
	captions[i]="Star Light Zone by John Weeks"
	midis[++i]="music/midis/sonic/1/s1starlightr.mid"
	captions[i]="Star Light Zone by Riwo"
	midis[++i]="http://www.geocities.com/EnchantedForest/Dell/7835/skcskysanctuary.mid"
	captions[i]="Sky Sanctuary Zone by SEGA"

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

	midis[++i]="/music/midis/sonic/3k/flyingbattery2-k.mid"
	captions[i]="Flying Battery Act 1 by Koryan"
	midis[++i]="http://www.geocities.com/enchantedforest/dell/7835/skcflyingbattery.mid"
	captions[i]="Flying Battery Act 1 by SEGA"
	midis[++i]="music/midis/sonic/3dcd/panicpuppetjr.mid"
	captions[i]="Panic Puppet Zone Act 1 by Jeff Read"

	var bass=i;

	midis[++i]="http://www.geocities.com/EnchantedForest/Dell/7835/kcasolatedislandk3.mid"
	captions[i]="Door Into Summer (Isolated Island Zone) (Version 3) by Koryan"
	midis[++i]="music/midis/sonic/chaotix/kcbotonicbasek3.mid"
	captions[i]="Midnight Greenhouse (Botanic Base Zone) (Version 3) by Koryan"
	midis[++i]="music/midis/sonic/chaotix/kcspeedsliderk2.mid"
	captions[i]="Speed of Sound (Speed Slider Zone) (Version 2) by Koryan"
	midis[++i]="http://www.geocities.com/EnchantedForest/Dell/7835/s3creditsek3.mid"
	captions[i]="Sonic 3 Credits Mix 3 by Edan Koch"
	midis[++i]="music/midis/sonic/s1g/gs1bridgejr.mid"
	captions[i]="Bridge Zone (Version 1) by John Weeks"
	midis[++i]="http://www.geocities.com/EnchantedForest/Dell/7835/SE.mid"
	captions[i]="Sonic Electronic by Jeff Read"
	midis[++i]="http://www.geocities.com/EnchantedForest/Dell/7835/KR.mid"
	captions[i]="King of the Ring (Radio Zone) by Jeff Read"
	midis[++i]="music/midis/south-island.mid"
	captions[i]="South Island"
	midis[++i]="music/midis/sonic/3dblast/rustyruin-act2-jw.mid"
	captions[i]="Rusty Ruin Zone Act 2 Genesis by John Weeks"

	//midis[++i]="http://www.geocities.com/EnchantedForest/Dell/7835/kcasolatedislandk3.mid"
	//captions[i]="Diamond Dust Zone Act 1 Saturn by Jarel Jones and JD Harding"
	//midis[++i]="music/midis/sonic/cdpast/wackyworkbench-past-jw.mid"
	//captions[i]="Wacky Workbench Past by John Weeks"
	//midis[++i]="http://www.geocities.com/EnchantedForest/Dell/7835/kcasolatedislandk3.mid"
	//captions[i]="Labyrinth Zone by John Weeks and Jordan Savik"
	// stardust speedway all, more mm midis, 

var nummidis = i;
day = new Date()
seed = day.getTime()
ran = parseInt(((seed - (parseInt(seed/1000,10) * 1000))/10)/100*nummidis + 1,10)

var midi = midis[ran];
var caption = captions[ran];

if(ran <= space) theme = "space";
else if(ran <= ice) theme = "ice";
else if(ran <= bass) theme = "bass";

// mm themes - space, ice, mega man, forte, roll, blues, zero, mmx
// sonic themes - space, ice, sonic, metal sonic, tails, knuckles, espio, vector
// others - chaos, tikal, chao, ray, mighty, charmy, big, amy, e-102, rush, beat, tango, dr. light