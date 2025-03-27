# Software


## Prérequis
### Installation de ROS2 Jazzy

### Installation du driver EtherCAT igh Master de chez EtherLab

Pour cela nous recommandons d'utiliser le package Debian 

### Installation de ethercat_ros2_driver pour Jazzy

.. code-block:: console

    $ sudo apt-get update
    $ sudo apt-get upgrade
    $ sudo apt-get install git autoconf libtool pkg-config make build-essential net-tools

### Installation du controleur ViproHead


## Compilation du contrôleur de VIPROHEAD

###  Utilisation du controleur

colcon build --symlink-install

source /opt/ros/humble/setup.bash
