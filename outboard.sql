-- phpMyAdmin SQL Dump
-- version 4.2.5
-- http://www.phpmyadmin.net
--
-- Host: p3nlmysql101plsk.secureserver.net:3306
-- Generation Time: Dec 13, 2014 at 09:35 AM
-- Server version: 5.5.33-log
-- PHP Version: 5.5.14

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `outboard`
--
CREATE DATABASE IF NOT EXISTS `outboard` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE `outboard`;

-- --------------------------------------------------------

--
-- Table structure for table `outboard`
--

CREATE TABLE IF NOT EXISTS `outboard` (
`id` int(11) NOT NULL,
  `name` varchar(50) NOT NULL,
  `enabled` tinyint(1) NOT NULL,
  `status` tinyint(1) NOT NULL,
  `imagename` varchar(100) NOT NULL,
  `statustext` varchar(100) NOT NULL
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `outboard`
--
ALTER TABLE `outboard`
 ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `outboard`
--
ALTER TABLE `outboard`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=4;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
