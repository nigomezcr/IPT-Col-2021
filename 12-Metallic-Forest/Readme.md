# Problem 12: Metallic Forest

In the electrolysis of aqueous solutions of metal salts, fractal-like dendrites can begin to grow gradually on the electrodes. How can the dendrites shape and fractal dimension be controlled by choice and variation of the setup parameters?

### Code

This code use the library *OpenCV*. The installing procedure in Ubuntu is

```shell
sudo apt update
sudo apt install opencv
```

The code functions via Makefile. This file create the objects and executable files. Do in the shell

```shell
make
```

The executable name is  <span style="color:green">x.read_image</span>. But before we execute it we need the folder *Data_FD*. If is not created, create it via

```shell
mkdir Data_FD
```

The proccedure to use the code is the next one

```shell
./x.read_image Images/imagefile.ext
gnuplot -e "filename='imagefile'" plot.gp
```

The first command creates *imagefile.csv* and *imagefile_image.csv*. And the second onde the files *imagefile.log* and *imagefile.pdf*. All of them are going to be located in the *Data_FD* folder.

- ###### *imagefile.csv*:
  
  Data for fitting. First column is $\epsilon$ (size of box) and the second is *N* (Number of boxes where the fractal image is).
- ###### *imagefile_image.csv*:
  
  Image's points used to calculate *N*. The plotting of this file give the image of the effective figure that was used after the Digital Image Processing.
- ###### *imagefile.log*:
  
  Fitting information. *Gnuplot* give us a detailed information, in this file, about the fitting done.
- ###### *imagefile.pdf*:
  
  Plot of data and fitted curve. The PDF file contains the data in log-log scale and its respective fitting curve. There also appears the <u>Haussdorf dimension</u> ($dim_H$) and $\chi^2$ fitting value.
  
  

##### Note:

Gnuplot is using a different font. *Mf Young & Beatiful* font is used as default. Here we give instructions to install it.

1.  Download the *.otf and *.ttf files in [Mf Young & Beautiful](https://www.onlinewebfonts.com/download/3285fac66b977678d22418cd557e01b0).

2. Create the folder, unzip the file and move the files to the fonts folder.
   
   ```shell
   mkdir Mf_Young_&_Beautiful
   cd Mf_Young_&_Beautiful
   unzip ../OnlineWebFonts_*.zip
   sudo cp -R 'Mf Young & Beautiful' /usr/share/fonts/
   ```