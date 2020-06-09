<?php

namespace Uci\Bee4all;


class Uci{

    private $uci;

    public function __construct()
    {
        $uci = FFI::load(__DIR__ . '/lib/uciu.h');
    }


    public function getUci(){


        return $this->uci;
    }
}

?>