int teamid (std::string team) {
	if (team.compare("BOS") == 0) {
		return 1;
	} else if (team.compare("BKN") == 0) {
		return 2;
	} else if (team.compare("NYK") == 0) {
		return 3;
	} else if (team.compare("PHI") == 0) {
		return 4;
	} else if (team.compare("TOR") == 0) {
		return 5;
	} else if (team.compare( "CHI") == 0) {
		return 6;
	} else if (team.compare("CLE") == 0) {
		return 7;
	} else if (team.compare("DET") == 0) {
		return 8;
	} else if (team.compare("IND") == 0) {
		return 9;
	} else if (team.compare("MIL") == 0) {
		return 10;
	} else if (team.compare("ATL") == 0) {
		return 11;
	} else if (team.compare("CHA") == 0) {
		return 12;
	} else if (team.compare("MIA") == 0) {
		return 13;
	} else if (team.compare("ORL") == 0) {
		return 14;
	} else if (team.compare("WAS") == 0) {
		return 15;
	} else if (team.compare("DEN") == 0) {
		return 16;
	} else if (team.compare("MIN") == 0) {
		return 17;
	} else if (team.compare("OKC") == 0) {
		return 18;
	} else if (team.compare("POR") == 0) {
		return 19;
	} else if (team.compare("UTA") == 0) {
		return 20;
	} else if (team.compare("GSW") == 0) {
		return 21;
	} else if (team.compare("LAC") == 0) {
		return 22;
	} else if (team.compare("LAL") == 0) {
		return 23;	
	} else if (team.compare("PHX") == 0) {
		return 24;
	} else if (team.compare("SAC") == 0) {
		return 25;
	} else if (team.compare("DAL") == 0) {
		return 26;
	} else if (team.compare("HOU") == 0) {
		return 27;
	} else if (team.compare("MEM") == 0) {
		return 28;
	} else if (team.compare("NOP") == 0) {
		return 29;
	} else if (team.compare("SAS") == 0) {
		return 30;
	}
	return -1;
}

int teamid_full (std::string team) {
    if (team.compare("Boston Celtics") == 0) {
        return 1;
    } else if (team.compare("Brooklyn Nets") == 0) {
        return 2;
    } else if (team.compare("New York Knicks") == 0) {
        return 3;
    } else if (team.compare("Philadelphia 76ers") == 0) {
        return 4;
    } else if (team.compare("Toronto Raptors") == 0) {
        return 5;
    } else if (team.compare("Chicago Bulls") == 0) {
        return 6;
    } else if (team.compare("Cleveland Cavaliers") == 0) {
        return 7;
    } else if (team.compare("Detroit Pistons") == 0) {
        return 8;
    } else if (team.compare("Indiana Pacers") == 0) {
        return 9;
    } else if (team.compare("Milwaukee Bucks") == 0) {
        return 10;
    } else if (team.compare("Atlanta Hawks") == 0) {
        return 11;
    } else if (team.compare("Charlotte Hornets") == 0) {
        return 12;
    } else if (team.compare("Miami Heat") == 0) {
        return 13;
    } else if (team.compare("Orlando Magic") == 0) {
        return 14;
    } else if (team.compare("Washington Wizards") == 0) {
        return 15;
    } else if (team.compare("Denver Nuggets") == 0) {
        return 16;
    } else if (team.compare("Minnesota Timberwolves") == 0) {
        return 17;
    } else if (team.compare("Oklahoma City Thunder") == 0) {
        return 18;
    } else if (team.compare("Portland Trail Blazers") == 0) {
        return 19;
    } else if (team.compare("Utah Jazz") == 0) {
        return 20;
    } else if (team.compare("Golden State Warriors") == 0) {
        return 21;
    } else if (team.compare("Los Angeles Clippers") == 0) {
        return 22;
    } else if (team.compare("Los Angeles Lakers") == 0) {
        return 23;
    } else if (team.compare("Phoenix Suns") == 0) {
        return 24;
    } else if (team.compare("Sacramento Kings") == 0) {
        return 25;
    } else if (team.compare("Dallas Mavericks") == 0) {
        return 26;
    } else if (team.compare("Houston Rockets") == 0) {
        return 27;
    } else if (team.compare("Memphis Grizzlies") == 0) {
        return 28;
    } else if (team.compare("New Orleans Pelicans") == 0) {
        return 29;
    } else if (team.compare("San Antonio Spurs") == 0) {
        return 30;
    }
    return -1;
}


std::string team_idTOname (double team) {
	if (team == 1) {
		return "BOS";
	} else if (team == 2) {
		return "BKN";
	} else if (team == 3) {
		return "NYK";
	} else if (team == 4) {
		return "PHI";
	} else if (team == 5) {
		return "TOR";
	} else if (team == 6) {
		return "CHI";
	} else if (team == 7) {
		return "CLE";
	} else if (team == 8) {
		return "DET";
	} else if (team == 9) {
		return "IND";
	} else if (team == 10) {
		return "MIL";
	} else if (team == 11) {
		return "ATL";
	} else if (team == 12) {
		return "CHA";
	} else if (team == 13) {
		return "MIA";
	} else if (team == 14) {
		return "ORL";
	} else if (team == 15) {
		return "WAS";
	} else if (team == 16) {
		return "DEN";
	} else if (team == 17) {
		return "MIN";
	} else if (team == 18) {
		return "OKC";
	} else if (team == 19) {
		return "POR";
	} else if (team == 20) {
		return "UTA";
	} else if (team == 21) {
		return "GSW";
	} else if (team == 22) {
		return "LAC";
	} else if (team == 23) {
		return "LAL";	
	} else if (team == 24) {
		return "PHX";
	} else if (team == 25) {
		return "SAC";
	} else if (team == 26) {
		return "DAL";
	} else if (team == 27) {
		return "HOU";
	} else if (team == 28) {
		return "MEM";
	} else if (team == 29) {
		return "NOP";
	} else if (team == 30) {
		return "SAS";
	} else {
		return "-1";
	}
}
