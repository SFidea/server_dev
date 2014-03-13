<?php
        //log function
        function logFile($filename,$msg){
	$fd = fopen($filename,"a");
	$str = "[".date("Y/m/d h:i:s",time())."]".$msg;
	fwrite($fd, $str."\n");
	fclose($fd);
        }

        $tokens=explode('/', $_GET['link']);
        $filename=$tokens[sizeof($tokens)-1];
        $folder1='det/';
        $folder2='crop/';
        $folder3='mesh/';
        $in_folder='uploads/';
   
        //call image detection
        //copy($in_folder. $filename, $folder1. $filename); //for simple test, copy the orginal from in_folder to folder
        //copy($in_folder. $filename, $folder2. $filename); //for simple test, copy the orginal from in_folder to folder
        //copy($in_folder. $filename, $folder3. $filename); //for simple test, copy the orginal from in_folder to folder
             

        $output = shell_exec('python /var/www/facedetect.py ' .$in_folder. $filename .' ' .$folder1. $filename .' ' .$folder2. $filename .' det');
        logfile('log.txt','output:' .$output);
        
      
      
      /*  if ($output==null){
        if (file_exists($in_folder .$filename)) {

        logfile('log.txt', $filename.' file exists');
    
        header('Content-Type: image/jpeg');
        readfile($in_folder .$filename);
        } else {
                logfile('log.txt','file ' .$filename .' NOT exists');
        }
        }*/
             
               
        
        if (file_exists($folder1 .$filename)) {

        logfile('log.txt', $filename.' file exists');
    
        header('Content-Type: image/jpeg');
        readfile($folder1 .$filename);
        } else {
                logfile('log.txt','file ' .$filename .' NOT exists');
        }
     
?>
