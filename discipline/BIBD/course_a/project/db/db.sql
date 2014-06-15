-- MySQL dump 10.13  Distrib 5.5.37, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: bikeshopdb
-- ------------------------------------------------------
-- Server version	5.5.37-0ubuntu0.12.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `available_bicycles`
--

DROP TABLE IF EXISTS `available_bicycles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `available_bicycles` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `availability` tinyint(1) DEFAULT NULL,
  `bicycles_count` int(11) DEFAULT NULL,
  `bicycle_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UK_an44nl7sgw0hthg5al88jw0` (`bicycle_id`),
  KEY `FK_an44nl7sgw0hthg5al88jw0` (`bicycle_id`),
  CONSTRAINT `FK_an44nl7sgw0hthg5al88jw0` FOREIGN KEY (`bicycle_id`) REFERENCES `bicycles` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `available_bicycles`
--

LOCK TABLES `available_bicycles` WRITE;
/*!40000 ALTER TABLE `available_bicycles` DISABLE KEYS */;
INSERT INTO `available_bicycles` VALUES (4,1,10,1),(5,1,15,2);
/*!40000 ALTER TABLE `available_bicycles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bicycles`
--

DROP TABLE IF EXISTS `bicycles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bicycles` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `brakes` varchar(255) DEFAULT NULL,
  `cassette` varchar(255) DEFAULT NULL,
  `chain` varchar(255) DEFAULT NULL,
  `color` varchar(255) DEFAULT NULL,
  `cranckset` varchar(255) DEFAULT NULL,
  `fork` varchar(255) DEFAULT NULL,
  `fork_move` int(11) DEFAULT NULL,
  `frame_materials` varchar(255) DEFAULT NULL,
  `front_derailer` varchar(255) DEFAULT NULL,
  `guarantee` varchar(255) DEFAULT NULL,
  `handlebar` varchar(255) DEFAULT NULL,
  `lockout` tinyint(1) DEFAULT NULL,
  `manufacturer` varchar(255) NOT NULL,
  `pedals` varchar(255) DEFAULT NULL,
  `photo_path` varchar(255) DEFAULT NULL,
  `price` double DEFAULT NULL,
  `product_name` varchar(255) NOT NULL,
  `rates_number` tinyint(4) NOT NULL,
  `rear_derailer` varchar(255) DEFAULT NULL,
  `saddle` varchar(255) DEFAULT NULL,
  `shifters` varchar(255) DEFAULT NULL,
  `bicycle_size` varchar(255) NOT NULL,
  `tires` varchar(255) DEFAULT NULL,
  `type` varchar(255) DEFAULT NULL,
  `weight` double DEFAULT NULL,
  `wheels_diameter` tinyint(4) NOT NULL,
  `year` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bicycles`
--

LOCK TABLES `bicycles` WRITE;
/*!40000 ALTER TABLE `bicycles` DISABLE KEYS */;
INSERT INTO `bicycles` VALUES (1,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Fuji',NULL,'pic/1.png',NULL,'Traverse 1.3',27,NULL,NULL,NULL,'M',NULL,NULL,NULL,28,2014),(2,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'GT',NULL,'pic/2.png',NULL,'Timberline 2.0',27,NULL,NULL,NULL,'M',NULL,NULL,NULL,28,2014);
/*!40000 ALTER TABLE `bicycles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `orders`
--

DROP TABLE IF EXISTS `orders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `orders` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `goods_cost` double NOT NULL,
  `order_date` date NOT NULL,
  `order_status` varchar(255) NOT NULL,
  `bicycle_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_q3pc5qwuyri8snomhqavssmhh` (`bicycle_id`),
  KEY `FK_k8kupdtcdpqd57b6j4yq9uvdj` (`user_id`),
  CONSTRAINT `FK_k8kupdtcdpqd57b6j4yq9uvdj` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `FK_q3pc5qwuyri8snomhqavssmhh` FOREIGN KEY (`bicycle_id`) REFERENCES `bicycles` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `orders`
--

LOCK TABLES `orders` WRITE;
/*!40000 ALTER TABLE `orders` DISABLE KEYS */;
/*!40000 ALTER TABLE `orders` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `orders_archive`
--

DROP TABLE IF EXISTS `orders_archive`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `orders_archive` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `goods_cost` double NOT NULL,
  `order_date` date NOT NULL,
  `bicycle_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_97beet5p210p64odvrtyji5d7` (`bicycle_id`),
  KEY `FK_bj5pakxyx6ujgog09474wcpux` (`user_id`),
  CONSTRAINT `FK_bj5pakxyx6ujgog09474wcpux` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `FK_97beet5p210p64odvrtyji5d7` FOREIGN KEY (`bicycle_id`) REFERENCES `bicycles` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `orders_archive`
--

LOCK TABLES `orders_archive` WRITE;
/*!40000 ALTER TABLE `orders_archive` DISABLE KEYS */;
INSERT INTO `orders_archive` VALUES (1,590,'2014-06-15',1,3);
/*!40000 ALTER TABLE `orders_archive` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `phone_number` varchar(255) NOT NULL,
  `user_role` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UK_6dotkott2kjsp8vw4d0m25fb7` (`email`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'admin@gmail.com','Admin','admin','8033445553322','ADMIN'),(3,'user@gmail.com','User','user','8033445553322','USER');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-06-15 19:26:42
