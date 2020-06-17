<?php

namespace Ucilib\Bee4all;




class Uci{

    private $uci;

    public function __construct()
    {
        $this->uci = \FFI::load(__DIR__ . '/lib/uciu.h');
    }


    public function getUci(){


        return $this->uci;
    }



    /**
     * @param array $liste
     * @return int
     */
    public function NbFieldUCI(Array $liste):int{

        return $this->uci->NbFieldUCI($liste);
    }


    /**
     * @param car $path
     * @return array
     */
    public function uciget_list(char $path):array {

        return $this->uci->uciget_list($path);
    }

    /**
     * @param char $path
     * @return integer
     *  retourne un entier correspond à l'entre path
     *
     */
    public function uciget_int(char $path): int {

        return $this->uci->uciget_string($path);
    }

    /**
     * @param char $path
     * @param char $value
     * @return int
     *
     *
     */
    public function uciget_string(char $path,char $value):int{

        return $this->uci->uciget_string($path,$value);
    }


    public function RemoveAllChars(){

    }

    /**
     * @param char $uuid
     * @param char $variable
     * @return int
     */
    public function uciGetModule_Int(char $uuid,char $variable):int{

        return $this->uic->uciGetModule_int($uuid,$variable);
    }

    /**
     * @param char $uuid
     * @param char $variable
     * @param char $value
     * @return string
     * returne un string dans value correspondant au module uuid pour la valeur variable
     */
    public function uciGetModule_String(char $uuid,char $variable,char $value):string {

        return $this->uciGetModule_String($uuid,$variable,$value);
    }

    /**
     * @param char $uuid
     * @param char $variable
     * @return array
     */
    public function uciGetModule_List(char $uuid,char $variable):array{

        return $this->uci->uciGetModule_List($uuid,$variable);
    }

    /**
     * @param char $uuid
     * @param char $variable
     * @param char $value
     * @return int
     */
    public function uciAddOption(char $uuid,char $variable,char $value):int{

        return $this->uci->uciAddOption($uuid,$variable,$value);
    }


    /**
     * @param char $uuid
     * @param char $variable
     * @param char $value
     * @return int
     */
    public function uciSetOption(char $uuid,char $variable,char $value):int{

        return $this->uci->uicSetOptions($uuid,$variable,$value);
    }

    /**
     * @param char $uuid
     * @param char $value
     * @return int
     */
    public function uciAddModule(char $uuid,char $value):int{
        return $this->uci->uciAddModule($uuid,$value);
    }


    /**
     * @param char $uuid
     * @return int
     */
    public function uciDeleteModule(char $uuid):int{

        return $this->uci->uciDeleteModule($uuid);
    }

    /**
     * @param char $uuid
     * @param char $variable
     * @return int
     */
    public function uciDeleteOption(char $uuid,char $variable):int{

        return $this->uci->uciDeleteOption($uuid,$variable);
    }

    /**
     * @param char $uuid
     * @param char $variable
     * @param char $value
     * @return int
     */
    public function uciAddList(char $uuid,char $variable,char $value):int{

        return $this->uci->uciAddList($uuid,$variable,$value);
    }


    /**
     * @param char $uuid
     * @param char $variable
     * @param char $value
     * @return int
     */
    public function uciDeleteList(char $uuid,char $variable,char $value):int{

        return $this->uci->uciDeleteList($uuid,$variable,$value);
    }

    /**
     * @param char $uuid
     * @param char $variable
     * @return int
     */
    public function uciDropList(char $uuid,char $variable):int{

        return $this->uci->dropList($uuid,$variable);
    }


    /**
     * @param char $request
     * @return array
     */
    public function uciGetListe(char $request): array{

        return $this->uci->uciGetListe($request);
    }


    /**
     * @param char $searchObject
     * @return int
     */
    public function uciModuleExiste(char $searchObject):int{

        return $this->uciModuleExiste($searchObject);
    }

    /**
     * @param char $uuid
     * @return int
     */
    public function uciCommitModule(char $uuid):int{

        return $this->uci->uciCommitModule($uuid);
    }

    public function UciReadModule(){

        return $this->uci->UciReadModule();
    }
}


?>