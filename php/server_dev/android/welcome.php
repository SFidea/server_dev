
<?php
//echo $_GET["name"];
//echo $_GET["num"]; 


//path to directory to scan
//$directory = "uploads/";
//$directory = $_GET["name"] . "/";

//get all image files with a .jpg extension.
//$images = glob($directory . "*.jpg");

//print each file name
//foreach($images as $image)
//{
//  echo  $image;
//} 

        
$encode2 = array("feed"=>array(
                        "entry"=>array(
                        array("title"=>array('$t'=>"1"), 'media$group'=>array('media$thumbnail'=>array(array("url"=>"http://157.182.38.37/1/1.jpg")))),
                        array("title"=>array('$t'=>"2"), 'media$group'=>array('media$thumbnail'=>array(array("url"=>"http://157.182.38.37/1/2.jpg")))),
                        array("title"=>array('$t'=>"3"), 'media$group'=>array('media$thumbnail'=>array(array("url"=>"http://157.182.38.37/1/3.jpg")))),
                        array("title"=>array('$t'=>"4"), 'media$group'=>array('media$thumbnail'=>array(array("url"=>"http://157.182.38.37/1/4.jpg")))),
                        array("title"=>array('$t'=>"5"), 'media$group'=>array('media$thumbnail'=>array(array("url"=>"http://157.182.38.37/1/5.jpg")))),
                        array("title"=>array('$t'=>"6"), 'media$group'=>array('media$thumbnail'=>array(array("url"=>"http://157.182.38.37/1/6.jpg")))),
                        array("title"=>array('$t'=>"7"), 'media$group'=>array('media$thumbnail'=>array(array("url"=>"http://157.182.38.37/1/7.jpg")))),
                        array("title"=>array('$t'=>"8"), 'media$group'=>array('media$thumbnail'=>array(array("url"=>"http://157.182.38.37/1/8.jpg")))),
                        array("title"=>array('$t'=>"9"), 'media$group'=>array('media$thumbnail'=>array(array("url"=>"http://157.182.38.37/1/9.jpg")))),
                        array("title"=>array('$t'=>"10"), 'media$group'=>array('media$thumbnail'=>array(array("url"=>"http://157.182.38.37/1/10.jpg")))),
                        array("title"=>array('$t'=>"11"), 'media$group'=>array('media$thumbnail'=>array(array("url"=>"http://157.182.38.37/1/11.jpg")))),

                     )
                ));
                    
                    
        
$feed = json_encode($encode2);
//$json_encode = json_encode($encode);
//echo $json_encode."<br/>";
echo $feed;


?>


