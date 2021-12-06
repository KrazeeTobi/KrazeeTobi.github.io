<!--

var theme = 2;
var midi = ("rnf-cold.mid")
var caption = ("Cold Man's Stage by Maelgrim")

var nummidis = 17;
var randomnumber = Math.random();
var ran = Math.round( (nummidis-1) * randomnumber) + 1 ;
day = new Date()
seed = day.getTime()
ran = parseInt(((seed - (parseInt(seed/1000,10) * 1000))/10)/100*nummidis + 1,10)

// Space MIDI List
	if (ran == (1))
{	midi="/sonichq/comics/midis/Starman.mid"
	caption="Star Man by Maelgrim"; theme=1
}
	if (ran == (2))
{	midi="/sonichq/geocities/EnchantedForest/Tower/4309/mm8Tengu.mid"
	caption="Tengu Man (Saturn) by Maelgrim"; theme=1
}
	if (ran == (3)) {
	midi=("https://web.archive.org/20011206000000/http://www.geocities.com/EnchantedForest/Glade/8862/Gravityman.mid")
	caption=("Gravity Man Echo Remix by Maelgrim"); theme=1}

	if (ran == (4)) {
	midi=("/sonichq/comics/midis/gravity_beetle.mid")
	caption=("Gravity Beetle"); theme=1}
// End Space MIDI List

// Ice MIDI List
	if (ran == (5)) {
	midi=("/sonichq/geocities/EnchantedForest/Dell/7835/ricecapwa.mid")
	caption=("Ice Cap Fast Remix by Wild Alpha")}

	if (ran==6) {
	midi=("/sonichq/geocities/EnchantedForest/Dell/7835/ricecapdb.mid")
	caption=("Ice Cap Epic by David Bulmer")}

	if (ran==7) {
	midi=("/sonichq/geocities/EnchantedForest/Dell/7835/ESAMetropolistrancezone.mid")
	caption=("Metropolis Trance Zone by Edan Koch")}

	if (ran==8) {
	midi=("/sonichq/geocities/EnchantedForest/Dell/6657/Take_the_Snow_Train.mid")
	caption=("Nights Into Dreams: Take the Snow Train!")}

	if (ran==9) {
	midi=("/sonichq/games/mm4-cossack3.mid")
	caption=("Dr. Cossack Stage 3 by Maelgrim")}

	if (ran==10); // leave defaults - cold man

	if (ran==11) {
	midi=("/sonichq/music/midis/mm/8/frost.mid")
	caption=("Frost Man's Stage by Maelgrim")}

	if (ran==12) {
	midi=("/sonichq/music/midis/mm/x/blizzard-buffalo.mid")
	caption=("Blizzard Buffalo's Stage")}

	if (ran==13) {
	midi=("/sonichq/music/midis/mm/6/blizzard.mid")
	caption=("Blizzard Man's Stage")}

// End Ice MIDI List

// Forest MIDI List
	if (ran == (14))
{	midi="/sonichq/music/midis/mm/7/slash.mid"
	caption="Slash Man by Maelgrim"; theme=3
}
	if (ran == (15))
{	midi="/sonichq/comics/midis/dkc2bram.mid"
	caption="DKC2 - Bramble Scramble"; theme=3
}
	if (ran == (16)) {
	midi="/sonichq/music/midis/mario/Bowserkp.mid"
	caption="Mario RPG - Bowser's Keep"; theme=3}

	if (ran == (17)) {
	midi="/sonichq/music/midis/mario/frstmaze.mid"
	caption="Mario RPG - Forest Maze"; theme=3}
// End Forest MIDI List

///sonichq/music/midis/sjmuseum.mid
///sonichq/music/midis/Greenhills.mid
///sonichq/music/midis/mm/ground.mid
///sonichq/music/midis/s3/azure.mid
///sonichq/music/midis/sk/mushh2.mid
///sonichq/music/midis/s2/aquaticruin1.mid
// forest/jungle? - slash, bramble scramble, gusty glade, forest maze, napalm?

// ruins/castle? - ground, bowser's keep, sword?, split mushroom?

// water? - labyrinth?

// -->