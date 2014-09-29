SIP-Express Media Server - special build with AMR-Codec
=======================================================

Important legal notice
======================

Before you decide to distribute AMR packages, you should read following notes!

These tarballs don't provide any 3GPP source code. It is downloaded from 3GPP during compilation. To use package compiled by this code, you may need a license from 3GPP.

AMR codecs incorporate several patents, held by Ericsson, Universite de Sherbrooke (VoiceAge) and Nokia. VoiceAge claims to provide patent portfolio for AMR codecs. Depending on law in your country, manufacturers and developers may need to get a license. Because it is a shared library, you may need special contract for each one application, which links against this library, directly or indirectly.

Build Instructions
==================

Simply type:

dpkg-buildpackage -rfakeroot -us -uc

Original README.md
==================

          +------------------------------------+
          | SIP Express Media Server  - README |
          +------------------------------------+


Introduction:

 SEMS is a free, high performance, extensible media server 
 for SIP (RFC3261) based VoIP services. 

 It is intended to complement proxy/registrar servers
 in VoIP networks for all applications where server-
 side processing of audio is required, for example away 
 or pre-call announcements, voicemail, or network side 
 conferencing. Another use case is for interconnecting
 SIP networks, where a back-to-back user agent (B2BUA)
 is required.

 SEMS can be used to implement simple high performance 
 components like announcement servers as building 
 blocks of more complex applications, or, using its powerful 
 framework for application development including back-to-back 
 user agent (B2BUA) and state machine scripting functionality, 
 complex VoIP services can be realized completely in SEMS. 
 
 SEMS supports all important patent free codecs out of the
 box (g711u, g711a, GSM06.10, speex, G.726, L16 and iLBC).
 There is a wrapper for the IPP G.729 codec implementation
 available. Integrating other codecs in SEMS is very simple
 (patented or not).

 SEMS shows very good performance on current standard
 PC architecture based server systems. It has sucessfully
 been run with 1200 G.711 conference channels on a quad-core
 Intel(R) Xeon at 2GHz (700 GSM, 280 iLBC channels), and up to 
 5000 channels on a dual quad Xeon at 2.9GHz. Its back-to-back
 user agent has been run with up to 19000 TPS on the latter
 machine. On the other hand it also runs on very small devices -
 for example small embedded systems like routers running OpenWRT,
 for which of course the achievable channel count is not that
 high.

License:

 SEMS is free (speech+beer) software. It is licensed under dual 
 license terms, the GPL (v2+) and proprietary license. This
 program is released under the GPL with the additional exemption
 that compiling, linking, and/or using OpenSSL is allowed.

 See doc/COPYING for details.

Applications:

 The following applications are shipped with SEMS :

 Announcements (Prompts, Ringbacktones, Pre-call-prompts):
  * announcement   plays an announcement


  * ann_b2b        pre-call-announcement, plays announcement 
                   before connecting the callee in B2BUA mode
 
  * announce_transfer  pre-call-announcement, plays announcement 
                   and then transfers the caller to the callee 
                   using REFER

  * early_announce (pre-call) announcement using early media (183),
                   optionally continues the call in B2BUA mode

  * precoded_announce plays preencoded announcements


 Voicemail/Mailbox
  * voicebox       users can dial in to the voicebox to check
                   their messages

  * annrecorder    users can record their personal greeting 
                   message

  * mailbox        auto-attendant that saves voicemails into
                   an IMAP server. Users can dial in to check
                   their messages (simpler version)

  * voicemail      records voice messages and sends them 
                   as email, saves them to a voicebox, or
                   both


 Conferencing

  * conference     enables many people to talk together 
                   at the same time

  * webconference  conference application that can be 
                   controlled from an external program, 
                   e.g. a website 

  * conf_auth      collect a PIN number, verify it against an 
                   XMLRPC authentication server and connects in 
                   B2BUA mode

  * pin_collect    collect a PIN, optionally verify it, and transfer
                   the call into a conference

 Back-to-back User Agent
  
  * sbc            flexible SBC application, supports
                    - identity change
                    - header manipulation (filter etc)
                    - (multihomed) RTP relay
                    - SIP authentication 
                    - Session timer, call timer, prepaid
                    etc
 App development

  * dsm            DSM state machine scripting (use this)

  * ivr            embedded Python interpreter for simple apps
  
  * py_sems        another embedded Python interpreter

 Misc
  * echo           test module to echo the caller's voice
 

  * callback       reject the call, call back caller later and have 
                   her enter a number to call in b2bua with media relay
                   mode

  * reg_agent     SIP REGISTER to register SEMS' contact to an aor


Developing and customizing Applications and services:

 SEMS comes with a set of example applications intended to help 
 development of custom services, including a calling card 
 application, a traffic generator, a component to control the 
 media server via XMLRPC, and announcements played from DB.

 DSM state machine scripting is a powerful yet simple method
 to rapidly implement custom applications. With this method,
 the service logic is written as an easy to understand 
 textual definition of a state machine, which is interpreted
 and executed for every call. The (domain specific) language 
 for defining state machines can be extended by implementing
 modules. A set of useful modules are shipped with SEMS, 
 including MySQL database access module, Python module, 
 conference support, Amazon AWS and more. 

 SEMS' core implements basic call and audio processing, 
 and loads plug-ins which extend the system. Audio
 plug-ins enable new codecs and file formats, 
 application plug-ins implement the services' logic.
 Other modules called component modules provide 
 functionality for other modules to use.

 You can easily extend SEMS by creating your own plug-ins.
 Applications can be written using the SEMS framework API 
 in C++, or in Python using an embedded python interpreter 
 of the ivr or py_sems modules, or the DSM.

Requirements:

 All requirements are optional.

 o Python version >= 2.3 for the ivr (embedded python interpreter)
    and py_sems
 o flite speech synthesizer for TTS in the ivr
 o lame >= 3.95 for mp3 file output, mpg123 for mp3 playback
 o spandsp library for DTMF detection and PLC
    (SEMS has its own implementations for both)
 o libZRTP SDK (http://zfoneproject.com) for ZRTP
 o libev for jsonrpc

How to get started with SEMS:

  To try out SEMS, the easiest is to get a release from 
  http://ftp.iptel.org/pub/sems/, unpack and install it 
  using the usual make && make install. After installation, the 
  configuration file /usr/local/etc/sems/sems.conf needs to be 
  adapted, especially the parameters "sip_ip", "media_ip",
  "load_plugins", "application".

  On Debian and Ubuntu, add the SEMS repository from OBS to 
  /etc/apt/sources.list:
     deb http://download.opensuse.org/repositories/home:/team-sems/Debian_5.0 ./
  and install SEMS packages with: 
   wget http://download.opensuse.org/repositories/home:/team-sems/Debian_5.0/Release.key \
        -O - |apt-key add -   
   apt-get update && apt-get install sems
  If you want to build SEMS from source on debian/derivatives, see below.

  On Fedora/CentOS, simply do 
   $ sudo yum install sems
  and sems package will be installed.
 
  You can also follow one of the tutorials linked from the SEMS homepage
  (e.g. http://ftp.iptel.org/pub/sems/doc/current/howtostart_noproxy.html).
  The Application Modules Documentation page then gives an 
  overview of the application modules that come with SEMS 
  (http://ftp.iptel.org/pub/sems/doc/current/AppDoc.html).
  
  If you are interested in writing your own applications, the 
  application development tutorial is a good start 
  (http://www.iptel.org/sems/sems_application_development_tutorial),
  together with the design overview 
  (http://www.iptel.org/files/semsng-designoverview.pdf) and the example
  applications (apps/examples/).
   
  SEMS needs to be told from the many possible applications that are
  loaded which one to run. You can simply set the application 
  in sems.conf, e.g. application=conference. You can also define an
  application mapping, i.e. numbers (R-URIs) that will be mapped to
  applications, see the explanation of 'application' parameter in 
  sems.conf.

Creating packages on debian (ubuntu, ...), here for wheezy:

   install debian package build tools:
   $ sudo apt-get install debhelper devscripts

   install dependencies:
   $  sudo apt-get install g++ make libspandsp-dev flite-dev libspeex-dev \
         libssl-dev python-dev python-sip-dev openssl libev-dev \
         libmysql++-dev libevent-dev libxml2-dev libcurl4-openssl-dev
   
   get the source: 
   $ wget ftp.iptel.org/pub/sems/sems-x.y.z.tar.gz ; tar xzvf sems-x.y.z.tar.gz
   or, for git master:
   $ git clone git://git.sip-router.org/sems

   $ cd sems-x.y.z ; ln -s pkg/deb/debian .

   set version in changelog if not correct
   $ dch -v x.y.z "SEMS x.y.z release"
   or:
   $ dch -b -v `git describe --always` "sems git master"
   
   build package:
   $ dpkg-buildpackage -rfakeroot -us -uc

   install sems and sems-python-modules packages in .. using dpkg.

Installed files using 'make install':

    /usr/local/sbin/sems                 : SEMS executable
    /usr/local/lib/sems/plug-in/*        : plug-ins
    /usr/local/lib/sems/audio/*          : default path for audio files
    /usr/local/lib/sems/ivr/*            : precompiled IVR scripts
    /usr/local/etc/sems/sems.conf        : configuration file
    /usr/local/etc/sems/etc/*            : modules configuration files
    /usr/local/share/doc/sems/README     : this README.

    source_path/scripts/sems[.redhat]    : example start-up scripts.
    source_path/sems.conf.example        : example configuration file.

Documentation:

  In the doc/ directory there is a set of files describing the
  applications shipped with SEMS, alongside some more documentation.
  Generate the doxygen documentation with 'make doc' in doc/doxygen_doc,
  that contains all these files as well.

  All this and more documentation is available online linked from 
  the SEMS homepage: 
    http://www.iptel.org/sems.

Support, mailing lists, bugs and contact:

  Please have a look at the documentation and other information on 
  the SEMS homepage (www.iptel.org/sems). 

  Best-effort support is given through the mailing lists for SEMS,
  sems@iptel.org and semsdev@iptel.org, which are the first address 
  to ask for help, report bugs and improvements. You need to be 
  subscribed to be able to post to the lists: http://lists.iptel.org.
  The mailing list archives at   http://lists.iptel.org/pipermail/sems/ 
  and http://lists.iptel.org/pipermail/semsdev/ can be a great help as
  well (especially with google site search on lists.iptel.org, e.g.
  http://www.google.com/coop/cse?cx=006590474108803368786%3A158hxzctv4u ). 

  The bug tracker for SEMS is at http://tracker.iptel.org/browse/SEMS
  Please submit all bugs, crashes and feature requests you encounter.

Authors:

  Raphael Coeffic (rco@iptel.org), the father of SEMS, 
  Stefan Sayer (stefan.sayer@gmail.com), current lead developer,
  and all contributors:
    Alex Gradinar
    Alfred E Heggestad
    Andreas Granig
    Andrey Samusenko
    Andriy I Pylypenko
    Anton Zagorskiy
    B. Oldenburg
    Balint Kovacs
    Bogdan Pintea
    Greger Viken Teigre
    Grzegorz Stanislawski
    Helmut Kuper
    Jeremy A
    Jiri Kuthan
    Juha Heinanen
    Matthew Williams
    Ovidiu Sas
    Peter Lemenkov
    Peter Loeppky
    Richard Newman
    Robert Szokovacs
    Rui Jin Zheng
    Tom van der Geer
    Ulrich Abend
   (if you feel you should be on this list, please mail to stefan.sayer@gmail.com)
 
  Special thanks to IPTEGO GmbH, iptelorg GmbH and TelTech Systems Inc. for 
  sponsoring development of SEMS.

Contributions:

  All kinds of contributions and bug fixes are very welcome, for 
  example new application or codec modules, documentation pages, howtos
  etc. Please email one of the lists or the authors.

  Please also have a look at the contributions license policy 
  (see doc/COPYING).
  
SEMS - the media-S in the SLAMP.
