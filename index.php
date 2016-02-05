<!DOCTYPE html>
<html lang="en-us">
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>NBA Game Prediction System</title>

	<!-- Load fonts -->
	<link href='http://fonts.googleapis.com/css?family=Montserrat' rel='stylesheet' type='text/css'>
	<link href='http://fonts.googleapis.com/css?family=Lora' rel='stylesheet' type='text/css'>

	<!-- Load css styles -->
	<link rel="stylesheet" href="css/pickmeup.css" type="text/css" />
	<link rel="stylesheet" href="css/jquery.selectbox.css" type="text/css" />
	<link rel="stylesheet" type="text/css" href="css/bootstrap.css" />
	<link rel="stylesheet" type="text/css" href="css/font-awesome.css" />
	<link rel="stylesheet" type="text/css" href="css/style.css" />
      <link href="http://code.jquery.com/ui/1.10.4/themes/ui-lightness/jquery-ui.css" rel="stylesheet">

      <style>
	 .progress-label {
	    float: left;
	    margin-left: 50%;
	    margin-top: 5px;
	    font-weight: bold;
	    text-shadow: 1px 1px 0 #fff;
	}
      </style>

</head>
<body>
	<div class="jumbotron home home-fullscreen" id="home">
		<div class="mask"></div>
		<a href="#" class="logo">
			<img src="img/logo.png" >
		
		</a>
		
		<a href="" class="menu-toggle" id="nav-expander"><i class="fa fa-bars"></i></a>
		<!-- Offsite navigation -->
		<nav class="menu">
			<a href="#" class="close"><i class="fa fa-close"></i></a>
			<h3>Menu</h3>
			<ul class="nav">
				<li><a data-scroll href="#home">Home</a></li>
				<li><a data-scroll href="#services">Prediction</a></li>
				<li><a data-scroll href="#portfolio">About</a></li>
				<li><a data-scroll href="#contact">Contact</a></li>
			</ul>
			<ul class="social-icons">
				<li><a href=""><i class="fa fa-facebook"></i></a></li>
				<li><a href=""><i class="fa fa-twitter"></i></a></li>
				<li><a href=""><i class="fa fa-dribbble"></i></a></li>
				<li><a href=""><i class="fa fa-behance"></i></a></li>
				<li><a href=""><i class="fa fa-pinterest"></i></a></li>
			</ul>
		</nav>
		<div class="container">
			<div class="header-info">
				<h1>NBA Game Prediction System</h1>
				<p>Web based NBA regular season games prediction software.
				</p>
				<a href="#services" class="btn btn-primary">Start Your Prediction</a>
			</div>
		</div>
	</div>
	<!-- Services section start -->
	<section id="services">
		<div class="container">
			<div class="row">
				<div class="col-md-4">
					<div class="service-item">
						<div class="icon"><i class="fa fa-diamond"></i></div>
						<a href = "#services" id = "dateSearch">
							<h3  >Search Game by Date</h3>
						</a>
						<p>	Get the games' schedule on selected date.
						</p>

					</div>
				</div>
				<div class="col-md-4">
					<div class="service-item">
						<div class="icon"><i class="fa fa-gear"></i></div>
						<h3>Search Game by Team(Under development)</h3>
						<p>	Get All schedule of one NBA team.
						</p>
					</div>
				</div>
				<div class="col-md-4">
					<div class="service-item">
						<div class="icon"><i class="fa fa-life-ring"></i></div>
						<h3>System Instruction</h3>
						<p>1. Choosing search by date or team. </p>
						<p>2. choosing the one game from search	</p>
					</div>
				</div>
			</div>
		</div>
		
		<?php if (isset($_POST['gameDate'])) {
				$gameDate = $_POST['gameDate'];
				$dateSearch = explode("-", $_POST['gameDate']);
				$dates = $dateSearch[0].$dateSearch[1].$dateSearch[2];
				$command = './searchGame '.$dates;
				$escaped_command = escapeshellcmd($command);
				//echo $escaped_command;
				exec($escaped_command, $gamesToday);
				//var_dump($A);

			} 
			//var_dump($dates); 
		?>	
		<div id = "options" style = 'display : none'  align="center" >
				  <div id = "dateOption" >
					<section>
						<form method = "post" action = "#dateOption">
						<h2>Choosing the Game date</h2><br>
								<article>
								<input type = "text" class="gameDate"  name = "gameDate" value = "<?php echo $gameDate; ?>">
								</article>
							<input type = "submit" id = "searchDateButton" name="submit" value = "Search">
						</form>
					
					<div id="progressbar"></div>
						
					</section>
				  </div>
				<div id = "scheduleResult">
						<?php 
							if (!empty($gamesToday) || isset($_GET['gameSelected'])) {
								/*if ($gamesToday[0] == "No games today! Please choose another date!") {
									//echo "<h2>No games on". $_POST['gameDate'] ."! Please choose another date!</h2>";
								} else if ($gamesToday[0] == "Please choosing a correct date!") {
									//echo "<h2>Please choosing a correct date!</h2>";
								} else {*/
									//echo count($gamesToday); 
										echo "<h2>There are ".count($gamesToday)." NBA games on ". $_POST['gameDate']. "</h2>";
							?>
							<form method = "post" action = "#prediction_board">
								<select id="gameSelected" name="gameSelected" onchange = "this.form.submit()">
									<option disabled selected> -- select a game -- </option>
								<?php
									foreach($gamesToday as $val) {
										$rowGame = explode(" ",$val);
										$item = $rowGame[0]."-".$rowGame[1]."-".$rowGame[3]."-".$rowGame[2]."-".$rowGame[4];
										$selected = $rowGame[0]." ".$rowGame[1]."  V.S. ".$rowGame[3];
										echo "<option value ='".$item."'>".$selected."</option>";
									}
								?>	
								</select>
							<?php } ?>
							
				</div>
				<div id = "prediction_board">
						<?php
							

								if (isset($_POST['gameSelected'])) {
								$gameSearch = $_POST['gameSelected'];
								$games = explode("-",$gameSearch);
								//var_dump($games);
								$gamePredict = $games[0].$games[1].$games[2];
								//var_dump($gamePredict);
								$realScoreHost = $games[3];
								$realScoreVisitor = $games[4];
								//var_dump($gamePredict);
								//var_dump($gameSearch);
								$command2 = './linearRegressionPredict '.$gamePredict;
								$escaped_command2 = escapeshellcmd($command2);
								//echo $escaped_command2;
								exec($escaped_command2, $A, $return);
								//var_dump($A);
								$predictResult = $A[16];
								//echo $games[1]." V.S ".$games[2]."<br>".$predictResult;
								

							} 
					
						if (count($games) == 5) {
								$srcHost = "img/teamLogos/".$games[1].".jpg";
								$srcVistitor = "img/teamLogos/".$games[2].".jpg";
								
								echo "<h2>".$games[1]."&nbsp &nbsp &nbsp &nbsp &nbsp &nbsp&nbsp &nbsp &nbsp&nbsp &nbsp &nbsp&nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp".$games[2]."</h2>";
								echo "<img src =".$srcHost." height='200' width='200'>". "&nbsp &nbsp &nbsp&nbsp &nbsp &nbsp";
								echo "<img src ='img/vs.jpg' height='200' width='200'>". "&nbsp &nbsp &nbsp&nbsp &nbsp &nbsp";
								echo "<img src =".$srcVistitor." height='200' width='200'>";
								echo "<br><h2>Real Score</h2>";
								echo "<br><h1>".$realScoreHost."&nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp ".$realScoreVisitor."</h1>";
								echo "<br><h2>Prediction Result</h2>";
								if ($predictResult >= 0 ) {
									echo "<br><h1><strong>".$games[1]."</strong> WIN  "."</h1>";
								} else {
									echo "<br><h2><strong>".$games[2]."</strong> WIN  "."</h2>";
								}
						}
					?>
				</div>

		
		</div>
	</section>

	<!-- Services section end -->


	<!-- Footer start -->
	<footer>
		<div class="container">
			<div class="row">
				<div class="col-md-8">
					<p>&copy; NBA prediction system by Kai Wu, Yang yi Chen</p>
				</div>
				<div class="col-md-4">
					<ul class="social-icons">
						<li><a href=""><i class="fa fa-facebook"></i></a></li>
						<li><a href=""><i class="fa fa-twitter"></i></a></li>
						<li><a href=""><i class="fa fa-dribbble"></i></a></li>
						<li><a href=""><i class="fa fa-behance"></i></a></li>
						<li><a href=""><i class="fa fa-pinterest"></i></a></li>
					</ul>
				</div>
			</div>
		</div>
	</footer>
	<!-- Footer end  -->

	<!-- Load jQuery -->
	<script type="text/javascript" src="js/jquery-1.11.2.min.js"></script>
	<script src="http://code.jquery.com/ui/1.10.4/jquery-ui.js"></script>
	<script type="text/javascript" src="js/jquery.pickmeup.js"></script>
	

	<script>var dateSearch = "<?php echo $dates;?>"</script>
	<script>var gameSearch = "<?php echo $gameSearch;?>"</script>
	<script>
		$(document).ready(function(){
			$("#dateSearch").click(function(){
				$("#options").show();
				//alert("11111");
				$('.gameDate').pickmeup({
					format  : 'Y-m-d',
					position: 'bottom',
					hide_on_select : true
				});
			});
			/*$("#searchDateButton").click(function(){

			});*/
			
			
		if (dateSearch.length != 0) {
			$("#options").show();
			$('.gameDate').pickmeup({
				format  : 'Y-m-d',
				position: 'bottom',
				hide_on_select : true
			});
			//alert(dateSearch);
			//$('#gameSelected').selectBox();
		}
	//	alert(gameSearch.length);
		if (gameSearch.length != 0) {
			//alert(gameSearch);
			$("#options").show();
			
			$('.gameDate').pickmeup({
				format  : 'Y-m-d',
				position: 'bottom',
				hide_on_select : true
			});
		}
		/*$('.gameDate').pickmeup({
				format  : 'Y-m-d',
				position: 'bottom',
				hide_on_select : true
			});*/
		
	});
	</script>
	
	<!-- Load Booststrap -->
	<script type="text/javascript" src="js/bootstrap.js"></script>

	<script type="text/javascript" src="js/smooth-scroll.js"></script>

	<script type="text/javascript" src="https://maps.googleapis.com/maps/api/js?sensor=false"></script>

	<!-- Load custom js for theme -->
	<script type="text/javascript" src="js/app.js"></script>

</body>
</html>
