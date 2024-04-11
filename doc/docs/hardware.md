# Hardware specification

## Hardware description
Composition du dispositif expérimental :

* ViproHEAD 5 (fabriquant Viscotec) : tête d'impression 3D permettant de faire du micro-dosage de fluide monomatériaux
* EK1100 (fabriquant Beckhoff) : module de couplage EtherCAT
* EL7031 (fabriquant Beckhoff) : module de commande moteur pas-à-pas EL7031


## Extruder : ViproHEAD 5/5 from Viscotec

La tête d'impression ViproHEAD 5/5 est un composant clé du système de dosage Viscotec, conçu pour offrir des performances de dosage précises et 
fiables dans une variété d'applications industrielles. 
Cette documentation vise à fournir une vue d'ensemble complète de la tête d'impression, 
y compris ses caractéristiques, son fonctionnement, ses spécifications techniques et les meilleures pratiques pour son utilisation.

### Caractéristiques

La tête d'impression ViproHEAD 5/5 présente les caractéristiques suivantes :
* Technologie de dosage avancée pour une précision et une reproductibilité élevées
* Conception modulaire pour une maintenance facile et une polyvalence d'application
* Capacité à traiter une large gamme de fluides, y compris les fluides visqueux et abrasifs
* Intégration transparente avec les systèmes de dosage Viscotec pour une efficacité maximale

### Fonctionnement

La tête d'impression utilise un mécanisme de dosage basé sur une pompe à cavitation progressive contrôler par un moteur pas-à-pas, 
qui permet un contrôle précis du débit et du volume de fluide dispensé. 
Le système est conçu pour minimiser les pulsations et assurer une distribution uniforme du fluide, même dans des conditions de dosage exigeantes.

### Spécifications techniques

* Plage de débit : max volume flow 6 ml/min (dépend de la viscosité de la maitère et de la pression en entréeà
* Précision de dosage : min dosing quantity (ml at 1/12 rotation) 0.004 (mais dépend de la matière)
* Matériaux compatibles : Silicone Monocomposant RTV Wurth Pro A8
* Température de fonctionnement (température ambiante) : +10°C à +50°C
La documentation complète de la tête d'extrusion est disponible [ICI](datasheet/Vipro-HEAD3_5_manuel.pdf)

### Contrôle du moteur pas-à-pas 

Un moteur pas à pas est un dispositif électromagnétique qui se déplace par étapes discrètes. 
Il a plusieurs bobines qui sont organisées en phases. 
Lorsque chaque phase est mise sous tension à tour de rôle, le moteur marche. 
Avec les moteurs pas à pas, vous pouvez obtenir un positionnement précis et un contrôle de vitesse. 
Il existe trois principales façons de conduire un moteur pas à pas : full step drive, half-step drive et microstepping.
Il est impératif de sélectionner le bon moteur pas à pas pour vos exigences de vitesse et de couple en fonction de données telles que la taille du cadre, l’angle d’étape, le couple de maintien, le courant nominal, le nombre de fils, et unipolaire ou bipolaire.

Dans le cas du moteur de la tête d'extrusion ViproHEAD 5/5, le moteur pas-à-pas utilisé peut fonctionner en micro-stepping. La technique du micro-stepping consiste à créer des pas supplémentaires entre les pas physiques d'un moteur pas à pas. 
En clair, l'étage va ajouter des pas intermédiaires que l'on appellera micropas.
Il existe plusieurs configurations possibles :

* 1  1 pas de l'étage = 1 pas physique. On appelle çà le mode fullstep
* 1/2  2 micropas de l'étage par pas physique.
* 1/4  4 micropas de l'étage par pas physique.
* 1/8  8 micropas de l'étage par pas physique.
* 1/16  16 micropas de l'étage par pas physique.
* voire 1/32  32 micropas de l'étage par pas physique.

Le nombre de micropas total par tour vaut le nombre pas physiques du moteur mutliplié par le mode micropas. 

**Contrôle du débit  de la viproHEAD 5/5**

* Le moteur permet de faire $N_p= 200$ pas physique en un tour
* Il est équipé d'un réducteur  de rapport de réduction $r=1/12$
* En sortie de réducteur, nous obtenons $N_v = \frac{N_p}{r} = 2400$ pas physique par tour.
* Sachant que nous contrôlons le moteur en micro-stepping avec un mode 1/16, nous aurons alors $N = 16 N_v = 38400$ pas par tour, ce qui peut également se traduire par une résolution $0.009375$ $°$/pas

D'après la documentation technique de la tête d'extrusion, le volume dosé donné est $V_d = 0.05$ mL/tour, ce qui nous permet de connaître le volume dosé par pas : $\eta =\frac{V_d}{N} = \frac{0.05}{38400} = 1.3 \cdot 10^{-6}$ mL/pas. (ce qui est équivalent à $\eta = 1.3 \cdot 10^{-12}$ m$^3$ par pas)

Sachant que la vitesse de rotation du moteur est donnée par $\Omega_m$ en tour/min, on peut en déduire le débit en sortie d'extrudeur : $Q_{ext} = \Omega_m \eta$

En générale, dans le cadre de l'impression 3D, une filière est placée à la sortie de l'extrudeur. Cette filière se caractérise par une longueur $L_f$, une forme géométrique interne (conique, aiguille, cylindirique), et un diamètre de sortie $d_o$. Si l'on considère que le fluide s'écoule à travers cette filière sans perte de charge, c'est à dire que nous avons conservation du débit, alors on peut en déduire la vitesse d'écoulement du fluide, $V_{fluide}$, à partir de l'expression suivante : $Q_{ext} = V_{fluide} S_o$, sachant que $S_o$ est la section de la sortie de la filière (si on considère l'orificie de sortie circulaire alors $S_o=\pi \frac{d_o^2}{4}$). On a alors 

$V_{fluide} = \frac{4 \Omega_m V_d }{\pi N d_o^2}$

Cette expression ne tient pas compte du gonflement en sortie de filière. Théoriquement, si on souhaite déposer un cordon de silicone d'un diamètre équivalent à celui de l'orifice de sortie de la buse, alors il faudra que la buse se déplace à une vitesse de $V_{fluide}$.

* Remarques *
* Que cherchons nous à contrôler ? le débit à la sortie de la filière 

### Bonnes pratiques

Pour garantir des performances optimales de la tête d'impression ViproHEAD 5/5, il est recommandé de suivre les meilleures pratiques suivantes :

   - Nettoyer régulièrement la tête d'impression pour éviter l'accumulation de résidus
   - Vérifier et entretenir les composants clés conformément aux recommandations du fabricant
   - Suivre les procédures de calibration pour assurer la précision du dosage

## EtherCAT modules

### Module EK1100
Le module EK1100, développé par Beckhoff Automation, est un coupleur EtherCAT, permettant de connecter des modules esclaves EtherCAT à une réseau EtherCAT. 
C'est un module allimenté en 24V, que l'on peut connecté à un ordinateur contenant la pile EtherCAT de communication via un câble Ethernet. 
La documentation technique est disponible [ICI](datasheet/ek110x_ek15xxen.pdf).

### Module EL7031
Le module EL7031, développé par Beckhoff Automation, est une interface permettant de contrôler d'un moteur pas-à-pas, EL7031 (la documentation technique est accessible directement [ICI](datasheet/el70x1en.pdf).
Les étages de sortie PWM pour deux bobines de moteur se trouvent dans le terminal EtherCAT, ainsi que deux entrées pour les interrupteurs de fin de course. Le EL7031 peut être adapté au moteur et à l'application en modifiant seulement quelques paramètres. Le micro-pas 64 fois assure un fonctionnement particulièrement silencieux et précis du moteur.

## Câblage






