# Software


## Prérequis
Ubuntu 24.04 Noble installé sur un Raspberry Pi5
Noyau patché temps réel à partir du compte Ubuntu Pro (compte laurent Barbé)


### Installation de ROS2 Jazzy

### Installation du driver EtherCAT igh Master de chez EtherLab

Pour cela nous recommandons d'utiliser le package Debian [ICI](complement/code_1.98.2-1741788907_amd64.deb). 

.. note::

    Il est possible qu'avec la version Ubuntu 24.04, l'installation du package retourne une erreur sur poetry, il suffira alors de faire

    .. code-block:: console

      sudo apt install python3-poetry
      sudo apt update
      sudo apt upgrade

      
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
