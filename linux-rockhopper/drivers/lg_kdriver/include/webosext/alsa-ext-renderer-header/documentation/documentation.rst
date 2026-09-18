Documentation
=============

문서화 내용을 작성하는 사람을 위한 안내 페이지이다.

.. _Sphinx: https://www.sphinx-doc.org/
.. _restructuredText: https://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html
.. _rst: https://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html
.. _Doxygen Docblock: http://www.doxygen.nl/manual/docblocks.html

Overview
--------

배경:

`Linux Kernel의 문서화 <https://www.kernel.org/doc/html/latest/>`_,
`Linux Media Subsystem의 문서화 <https://linuxtv.org/downloads/v4l-dvb-apis-new/>`_
모두 Sphinx_ 기반의 문서화 시스템을 통해 관리하고 있어 본 프로젝트도 이와 동일 혹은 유사한 방식으로
문서를 관리하려고 한다.

규칙:

* 문서화 도구로 Sphinx_ 를 사용 (restructuredText_ - 이하 rst_, `Doxygen Docblock`_)

  * 하나의 페이지 안에서 문서 형식은 rst_ 형식을 따름
  * 서로의 페이지 연결은 rst_ 를 확장한 Sphinx_ 형식을 따름

* 모든 문서는 영문을 우선
* 파일 인코딩은 반드시 UTF-8을 사용
* 들여쓰기는 공백 2칸을 기본으로 하나 rst_ 의 들여쓰기 규칙을 우선
* 별 문제가 없을 경우 80칸을 기준으로 줄바꿈
* 서술어는 기본형을 사용(예, ``이다``, ``하다`` 를 사용하고 ``입니다``, ``합니다`` 사용 않음)

구성:

* Documentations for each Modules (Implementation Guide)
* Documentation for Status Files
* Documents for groups of some modules (*제안*)
* API Reference

배포:

http://10.157.92.177:8000/linuxtv 에 최신 버전을 매일 배포할 예정이며, 지난 버전 또한
유지를 한다.


도움:

http://hlm.lge.com/issue/browse/TVPLAT 프로젝트에 Task로 이슈를 생성하여
donghoon.keum@lge.com 또는 ashton.lee@lge.com 에게 assign 한다.


Module
^^^^^^

Module에 대한 문서화 페이지이다.
A module is a logical sub-unit of the entire LG Linux TV Driver.
Each module is managed into a single page in implementation guide pages
(Chapter 1-5).

The Guide pages of each module are categorized in:

* :doc:`/alsa`
* :doc:`/dvbv5`
* :doc:`/v4l2`
* :doc:`/voice`
* :doc:`/other` - not categorized above

각 category 안의 module 은 사전순으로 정렬되어 표시된다.

Status File
^^^^^^^^^^^

:doc:`/status-files` 에 대한 문서화 페이지이다.

Documents
^^^^^^^^^

:doc:`docs` 페이지는 연관 모듈이 하나의 기능이나 테마를 이룰 때 이에 대한 정보를 제공하는
페이지이다.

API Reference
^^^^^^^^^^^^^

소스파일(헤더파일)의 주석과 비슷한 Docblock 형식으로부터 추출되어 자동으로 생성된
:doc:`/api/index` 문서이다.

How to modify documents
---------------------------

.. image:: /doc_img/idx_page.png

Project Name
^^^^^^^^^^^^^

위 사진의 1번 빨간 박스 친 부분은 프로젝트 이름이다. ``Documentation/source/conf.py`` 에서
project 변수를 변경하면 된다.

Page Title
^^^^^^^^^^

첫 page를 구성하는 file은 ``index.rst`` 이다. 이 page 최상단의 'LG Linux TV Driver Implementation Guide' 를 변경하면 빨간박스 2번인 Title을 변경할 수 있다. string 아래의 ==== 는 최소 string 길이 만큼 쳐줘야 한다. 이는 다른 모든 page에도 동일하게 적용된다.

Documents Tree
^^^^^^^^^^^^^^^^^

빨간박스 3번 문서 트리 구조 수정 방법이다.
index.rst 에서 toctree 구문 아래 쪽을 수정하면 된다.
Behavioral Perspective Design 는 메뉴에서 보여지는 이름이고
<> 안에는 링크 할 rst 파일 이름을 확장자 제외하고 작성하면 된다.

.. image:: /doc_img/doctree.png

Sphinx & RST 문법
^^^^^^^^^^^^^^^^^^

스핑크스 및 RST 문법에 관련해서는 Sphinx_ 를 참조하면 된다.

Build Documentation
-------------------

Wall 에서 build 하기
^^^^^^^^^^^^^^^^^^^^^

wall에서 socts 문서 빛 binary build가 가능하다.
아래 사진과 같이 wall page에서 reply 버튼을 클릭하고 build +1 을 하면 된다.

.. image:: /doc_img/wall.png

약 5분 후 아래와같이 change log에 산출물의 경로가 표시된다.
다만 build error 시 아무것도 발생하지 않으며 어디서 error가 났는지 알 수 없다.

.. image:: /doc_img/build_result.png

따라서 아래에서 기술할 local build 방법을 추천한다.

Preparation
^^^^^^^^^^^

Requirements:

* 'doxygen' (version 1.6 or higher)
* 'python3' (version 3.6 or higher) and it's 'pip'

.. note::
  The simplest way to use 'doxygen' and 'python3' is install via package system
  (ex, ``apt``) with the root privilege.

  If you don't have the root privilege, you can install in user space locally.
  Build tools like 'gcc', 'make', 'cmake' must be required to install locally.

  In case of installation of 'doxygen', install commands may like this:

  .. code-block:: bash

    ## doxygen installation locally
    ## check more on http://www.doxygen.nl/manual/install.html#install_src_unix

    wget http://doxygen.nl/files/doxygen-1.8.16.src.tar.gz
    tar xf doxygen-1.8.16.src.tar.gz
    cd doxygen-1.8.16
    mkdir build
    cd build
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$HOME/local -Wno-dev ..
    make; make install

    ## doxygen will be installed in $HOME/local/bin
    ## modify PATH in your rc file like this:
    ## PATH=$PATH:$HOME/local/bin

  'doxygen' requires libraries 'bison', 'flex', and 'iconv'.
  If these libraries are not installed, you can install like this:

  .. code-block:: bash

    ## for example 'bison' library installation locally

    wget https://ftp.gnu.org/gnu/bison/bison-3.0.tar.gz
    tar xf bison-3.0.tar.gz
    cd bison-3.0
    ./configure --prefix=$HOME/local; make; make install

  The libraries may be OK for doxygen:

  * 'bison' version 2.0 or higher
  * 'flex' version 2.0 or higher
  * 'iconv' version 2.0 or higher

Next step requires 'python3'. You can check it's already installed via
``python3 --verison`` command. If it's not installed, install 'python3' via
package system with root privilege or `install using the source code
<https://docs.python.org/3/using/unix.html#building-python>`_.

Install python library requirements for documentation like below:

.. warning::
  If ``Documentation`` directory is not existed in project,
  switch to ``doc`` branch (``git checkout -b doc origin/doc`` or
  ``git switch -c doc origin/doc`` command).
  This situation shows the documentation is ready but not merged into master
  branch.

.. code-block:: bash

  $ cd (somewhere)/linuxtv-ext-header
  $ cd Documentation
  $ pip3 install -r requirements.txt

If last command is fail due to the permission problem, run
``pip3 install --user -r requirements.txt`` (see
https://pip.pypa.io/en/stable/reference/pip_install/#cmdoption-user).

After execution of last command ``sphinx-build`` must be executed. It may
located in ``/usr/bin`` or ``/usr/local/bin``. If not found, it may located in
``$HOME/.local/bin``. Append the directory to PATH environment variable.

Generate HTML
^^^^^^^^^^^^^

In ``Documentation`` directory:

.. code-block:: bash

  $ make clean html

위와 같이 실행하고 나면 ``build/html`` 디렉토리에 문서화 결과물이 생성되며,
브라우저를 통해 ``build/html/index.html`` 파일을 열어 확인할 수 있다.

View HTML with Python WebServer
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Open http://localhost:8000/ after:

.. code-block:: bash

  $ python3 -mhttp.server

or run in background:

.. code-block:: bash

  $ python3 -mhttp.server &

Generate without API Reference
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In ``Documentation`` directory:

.. code-block:: bash

  $ export LEH_DOC_DOXYGENINPUT=none
  $ make clean html

To unset:

.. code-block:: bash

  $ unset LEH_DOC_DOXYGENINPUT

Test Specific Modules in Fast
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In ``Documentation`` directory:

.. code-block:: bash

  $ export LEH_DOC_DOXYGENINPUT=../../linux/alsa-ext/alsa-ext-aenc.h
  $ make clean html

To unset:

.. code-block:: bash

  $ unset LEH_DOC_DOXYGENINPUT


Use Parallel Process
^^^^^^^^^^^^^^^^^^^^

In ``Documentation`` directory:

.. code-block:: bash

  $ export SPHINXOPTS="-j 6"
  $ make clean html

To unset:

.. code-block:: bash

  $ unset SPHINXOPTS

Test only Doxygen Syntax
^^^^^^^^^^^^^^^^^^^^^^^^

The `doxygen.conf` is not used to build documentation.
But it can be used to test DocBlocks in source codes.
*(This operation requires only `doxygen`)*

In ``Documentation`` directory:

.. code-block:: bash

  $ doxygen doxygen.conf > /dev/null

will prints all warnings and errors.

in ``html`` directory ``html/index.html`` is generated in doxygen output.

Documentation Templates
-----------------------

BSP Implementation Guide
^^^^^^^^^^^^^^^^^^^^^^^^^
BSP Implementation Guide 문서에 필수로 필요한 항목에 대하여 IEEE Stdandard-830 문서를 참고하여 작성되었다.

모듈 rst 파일 포맷 및 가이드
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
모듈의 BSP Implementation Guide 메인 페이지에 대한 내용을 작성하는 포맷 및 가이드이다.

.. seealso::

  참고 :doc:`/v4l2/scaler`

.. code-block:: rst

    Module Name
    ===========

    History
    -------

    ======= ========== ================= =======
    Version Date       Changed by        Comment
    ======= ========== ================= =======
    1.8.0   2022-03-29 seonghoon1128.do_ new kernel event CID : V4L2_CID_EXT_VSC_EVENT_KERNEL
    0.0.0   ...        ...               ...
    ======= ========== ================= =======

    Overall Description
    -------------------
    Write overall description.

    Terminology and Definitions
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^
    Definitions of terms and abbreviations used in this document are as follows.

    ============= ============
    Definition    Description
    ============= ============
    VFE           Video front end
    VSC           Video scaler control
    VDO           Video decoder output
    AVD           Analog video decoder
    ADC           Analog digital converter
    Dest          Destination
    ...           ....
    ...           ....
    ============= ============

    System Context
    ^^^^^^^^^^^^^^
    BSP 모듈과 플랫폼 서비스 또는 라이브러리의 인터페이스에 관한 동작 등에 관계를 나타낼 수 있는 System Context Diagram과 Diagram의 설명을 작성한다.
    Communication Diagram이 추천되나 다른 양식의 Diagram으로 작성될 수 있다.

    Performance Requirements
    ^^^^^^^^^^^^^^^^^^^^^^^^
    소프트웨어 또는 소프트웨어와 사람의 상호작용에 대하여 수치화된 정적/동적 요구사항이 명시되어야 한다.
    요구 사항이 없을 경우 특별한 요구사항이 없다고 작성한다.

    Design Constraints
    ^^^^^^^^^^^^^^^^^^
    다른 표준, 소프트웨어, 하드웨어 한계, 모듈의 특성 등에 의해 부과될 수 있는 제약사항을 명시해야 한다.
    요구 사항이 없을 경우 특별한 요구사항이 없다고 작성한다.

    Functional Requirements
    -----------------------
    The data types and functions used in this module are as follows.

    Data Types
    ^^^^^^^^^^

    * Parameter에 대한 data type 을 나열한다.
    * No data types
    * :c:type:`acas_ext_control`

    Function Calls
    ^^^^^^^^^^^^^^

    * Function에 대한 List를 작성한다.
    * no function calls
    * :c:macro:`ACAS_EXT_S_CTL`

API function 요구사항 헤더 파일 포맷 및 작성 가이드
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
모듈의 각 API function에 대한 요구사항을 작성하는 포맷 및 가이드이다.

.. seealso::

  참고 :c:macro:`V4L2_CID_EXT_VSC_ORBIT_WINDOW`

(based on v4l2 docs)

.. code-block:: rst

  /**
   * @brief Connects Video Front End (간단한 설명을 작성한다.)
   *
   * @rst
   * Functional Requirements
   *   API interface에 대한 요구사항을 작성한다.
   *
   * Responses to abnormal situations, including
   *   Abnormal situations, negative 조건에서의 BSP 예외처리에 대해 작성한다.
   *
   * Performance Requirements
   *   해당 Interface에 관련된 Performance Requirements 를 작성한다.
   *   요구사항이 없을 경우 특별한 요구사항이 없다고 작성한다.
   *
   * Constraints
   *   다음과 같이 개발자의 선택을 제한할 모든 항목에 관한 일반적인 설명을 제공해야 한다.
   *   Regulatory plocies
   *   Hardware limitations (e.g., signal timing requirements)
   *   Interfaces to other applications
   *   Parallel operation
   *   Audit functions
   *   Control functions
   *   Higher-order language requirements
   *   Signal handshake protocols(e.g., XON-XOFF, ACK-NACK)
   *   Reliability requirements
   *   Criticality of the application
   *   Safety and security considerations
   *   요구사항이 없을 경우 특별한 요구사항이 없다고 작성한다.
   *
   * Functions & Parameters
   *   .. code-block:: cpp
   *
   *     // function or command 나열
   *
   *     // parameter 나열
   *
   * Return Value
   *   Return Value에 관한 설명을 작성한다.
   *
   * Control Type
   *   Function 원형 또는 ioctl command 를 작성한다.
   *
   * Example
   *   .. code-block:: cpp
   *
   *     // 유저의 API function 사용 샘플코드를 작성한다.
   *
   * Remark (optional)
   *   description
   *
   * Seealso (optional)
   *   description
   * @endrst
   */

미사용 API 예외처리
^^^^^^^^^^^^^^^^^^^
미사용 API의 경우 module rst 문서와 module header, 두군데를 수정하여야 한다.
module rst 문서는 Documentation 아래에 있다.
Function Calls 아래에 아래와 같이 미사용 API에 대한 내용을 작성한다.
사용하는 함수들 아래쪽에 deprecated를 사용하여 작성해 준다.

.. code::

   * :c:macro:`V4L2_CID_EXT_HDMI_VIDEO_STATUS`
   * :c:macro:`V4L2_CID_EXT_HDMI_AUDIO_STATUS`
   * :c:macro:`V4L2_CID_EXT_HDMI_HDCP_STATUS`
   * :c:macro:`V4L2_CID_EXT_HDMI_SCDC_STATUS`
   * :c:macro:`V4L2_CID_EXT_HDMI_ERROR_STATUS`
   * :c:macro:`V4L2_CID_EXT_HDMI_EXPERT_SETTING`
   * :c:macro:`V4L2_CID_EXT_HDMI_OVERRIDE_EOTF` 

   .. deprecated:: webOS6.0
      it will be removed from webOS 24

      * :c:macro:`V4L2_CID_EXT_HDMI_PACKET_INFO`
      * :c:macro:`V4L2_CID_EXT_HDMI_PACKET_INFO`


deprecated 뒤는 이 함수가 webOS 어느버전 부터 사용되지 않았는지를 작성한다.
스핑크스 문법 때문에 webOS6.0처럼 webOS와 숫자를 붙여 사용해야 한다.
그리고 아래와 같이 webOS 어떤 버전에서 삭제될 예정인지 작성해야 한다.
it will be removed from (webOS 버전)


header는 아래와 같이 기존 주석에 @deprecated를 추가 후 작성하면 된다.

.. code::

   /**
   * @brief Initialize PVR Crypto
   *
   * @deprecated
   *  Deprecated since webOS 5.0, it will be removed from webOS 24


포맷은 Deprecated since (webOS버전), it will be removed from (webOS 버전) 이다.


Status File
^^^^^^^^^^^

.. seealso::

  For example :doc:`/status-files/scaler-status`, :doc:`/status-files/aenc-status`

(Not yet)

How to add attachemnts
^^^^^^^^^^^^^^^^^^^^^^
추가 정보를 위하여 file을 첨부할 대는 아래와 같은 형식을 사용한다.

.. code::

  :download:`example <../example.pdf>`

example은 문서에 표시될 이름이고 <> 안은 현재 작성중인 rst 파일과 첨부할 파일의 상대 경로 및 이름이다.
첨부파일은 현재 작성하고 있는 file 과 같은 depth 에 두는 것을 추천한다.
html 로 볼 경우 위의 tag를 누르면 바로 파일이 다운로드 가능하다.
하지만 PDF로 변환할 경우 해당 download tag는 동작하지 않는다. BSP 업체 담당자들의 경우 PDF로 볼 확률이
높기 때문에 이에 대한 가이드가 추가로 필요하다.

따라서 첨부파일이 필요할 경우 아래와 같이 작성한다.

.. code::
	
  if you see this page in HTML, please click below tag.
	example

  if you see this page in PDF, please check the example.pdf in attachment tab of Adobe Reader
  (View > Show/Hide > Navigation Panes > Attachments)


API exception for SoCTS
^^^^^^^^^^^^^^^^^^^^^^^

SoCTS Coverage(http://swdev.lge.com/coverage.html)에서는 header에 선언된 API 중 얼마나 SoCTS에 구현되었는가를 표시 하고 있다.
이런 저런 사정에 의하여 SoCTS로의 구현이 불가능할 경우 Coverage에서 미구현된 API로 집계되는 것을 피해야 한다.
그것을 위한 예외처리 방법을 아래에 설명한다.

규칙은 Function Calls 함수 이름 옆에 '//except from socts, TAS schedule:년.월' 을 적는 것이다.
TAS schedule은 파트의 TAS test 구현 일정을 말한다.
년월은 2022.08과 같이 년은 4개, 월은 2개의 숫자기한다.

이미 tas 구현이 완료되었거나 기타 사유등으로 socts test를 구현하지 않은 경우는
'//except from socts, it can be only verified by TAS' 와 같이 '//except from socts, 사유' 를
영어로 작성하면 된다.

.. code-block:: rst

  API_NAME //except from socts, TAS schedule:2022.08

실제 rst 파일의 예시이다.

.. code-block:: rst

  Function Calls
  --------------

  * Extended V4L2 Control ids

    * :c:macro:`V4L2_CID_EXT_HDMI_HPD_LOW_DURATION_DC_ON`
    * :c:macro:`V4L2_CID_EXT_HDMI_HDCP_REPEATER_TOPOLOGY` //except from socts, TAS schedule:2022.08
    * :c:macro:`V4L2_CID_EXT_HDMI_HDCP_REPEATER_STREAM_MANAGE`  //except from socts, TAS schedule:2022.08

위의 코드가 build가 완료되면 하기와 같이 html에서 표현된다.

.. image:: exception_socts.PNG

참고:

* https://linuxtv.org/downloads/v4l-dvb-apis/uapi/v4l/vidioc-queryctrl.html#vidioc-queryctrl
