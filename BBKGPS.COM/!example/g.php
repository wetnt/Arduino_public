<?php
    //==============================================================================
	include "bbk_php/congif.php";
    //==============================================================================
	include "bbk_php/bbk_GetUrl_Magic.php";//去除URL系统对JSON数据添加的引号！
	include "bbk_php/bbk_GetIdByNamePass_V9LG.php";
	include "bbk_php/bbk_Save_GpsLog_V9LG.php";
	include "bbk_php/bbk_Save_GpsMsg_V9MG.php";
    //==============================================================================
?>
<?php //json_decode(all);
    //==============================================================================
	//http://localhost/g.php?n=boboking&p=123456&g=39,116,50,80,180,1382678633000
	//http://www.boboking.com/v/g.php?n=boboking&p=123xjp&g=39,116,50,80,180,1382678633000
    //==============================================================================
	@$use_name = $_GET['n']; //ECHO $use_name.'<BR>';
	@$use_pass = $_GET['p']; //ECHO $use_pass.'<BR>';
	@$gps_logs = $_GET['g']; //ECHO $gps_logs.'<BR>';
    //==============================================================================
	@$use_idid = GetIdByNamePass_V9LG($use_name,$use_pass); // 帐户验证
	if( $use_idid <= -1){ DIE("User Name/Pass Error!"); }
    //==============================================================================
    $GPS = explode(",", $gps_logs); 
	//PRINT_R($GPS);ECHO '<BR>';
	//ECHO COUNT($GPS).'<BR>';
	if( COUNT($GPS) < 6){ DIE("GPS.length < 6"); }
    //==============================================================================
	$w = $GPS[0];	$j = $GPS[1];	$h = $GPS[2];
	$v = $GPS[3];	$f = $GPS[4];	$t = $GPS[5];
    //==============================================================================
	$gps_qry = Save_GpsLog_V9LGS($use_idid,$w,$j,$h,$v,$f,$t);
    //==============================================================================
	if( $gps_qry ){ DIE("UpLoadOK"); }else{ DIE("UpLoadERR"); }
    //==============================================================================
?>