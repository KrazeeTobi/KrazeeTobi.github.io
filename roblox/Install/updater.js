function doCheckRobloxInstall(minimalClientVersion, installPath, updatePath) {
	try {
		var robloxUpdater = new ActiveXObject("RobloxInstall.Updater");

		// See if product is out of date
		if (robloxUpdater.Version == "") {
			window.navigate(updatePath);
			return false;
		}
		if (robloxUpdater.IsVersionLessThan(minimalClientVersion)) {
			window.navigate(updatePath);
			return false;
		}
	} catch(e) {
		// failure indicates Roblox is not properly installed - install product:
		window.navigate(installPath);
		return false;
	}
	return true;
}

