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
    public function NbFieldUCI( $liste):int{

        return $this->uci->NbFieldUCI($liste);
    }


    /**
     * @param car $path
     * @return array
     */
    public function uciget_list( $path):array {

        $retour=$this->uci->uciget_list($path);
        $array=[];
        do{

            $res=FFI::string($retour->Value);
            $array[]=$res;
        }while($retour->Next!=null);
    }

    /**
     * @param char $path
     * @return integer
     *  retourne un entier correspond à l'entre path
     *
     */
    public function uciget_int( $path): int {

        return $this->uci->uciget_int($path);
    }

    /**
     * @param char $path
     * @param char $value
     * @return int
     *
     *
     */
    public function uciget_string( $path){

        $value=$this->uci->new("value_t");
        $retour=$this->uci->uciget_string($path,$value);
        $ret=new \stdClass();
        $ret->retour=$retour;
        $ret->value=$value;
        return $ret;

    }


    public function RemoveAllChars(){

    }

    /**
     * @param char $uuid
     * @param char $variable
     * @return int
     */
    public function uciGetModule_Int( $uuid, $variable):int{

        return $this->uic->uciGetModule_int($uuid,$variable);
    }

    /**
     * @param char $uuid
     * @param char $variable
     * @param char $value
     * @return string
     * returne un string dans value correspondant au module uuid pour la valeur variable
     */
    public function uciGetModule_String( $uuid, $variable ):string {

             $value=$this->uci->new("value_t");
             $retour=$this->uciGetModule_String($uuid,$variable,$value);
            $ret=new \stdClass();
            $ret->retour=$retour;
            $ret->value=$value;
            return $ret;
    }

    /**
     * @param char $uuid
     * @param char $variable
     * @return array
     */
    public function uciGetModule_List( $uuid, $variable):object{

        $retour=$this->uci->uciGetModule_List($uuid,$variable);
        $array=[];
        do{
            $res=explode(",",FFI::string($retour->Value));
            $array[]=array("mac"=>$res[0],"actif"=>$res[1]);

        }while($retour->Next!=null);


        return $array;
    }

    /**
     * @param char $uuid
     * @param char $variable
     * @param char $value
     * @return int
     */
    public function uciAddOption( $uuid, $variable, $value):int{

        return $this->uci->uciAddOption($uuid,$variable,$value);
    }


    /**
     * @param char $uuid
     * @param char $variable
     * @param char $value
     * @return int
     */
    public function uciSetOption( $uuid, $variable, $value):int{

        return $this->uci->uicSetOptions($uuid,$variable,$value);
    }

    /**
     * @param char $uuid
     * @param char $value
     * @return int
     */
    public function uciAddModule( $uuid, $type):int{
        return $this->uci->uciAddModule($uuid,$type);
    }


    /**
     * @param char $uuid
     * @return int
     */
    public function uciDeleteModule( $uuid):int{

        return $this->uci->uciDeleteModule($uuid);
    }

    /**
     * @param char $uuid
     * @param char $variable
     * @return int
     */
    public function uciDeleteOption( $uuid, $variable):int{

        return $this->uci->uciDeleteOption($uuid,$variable);
    }

    /**
     * @param char $uuid
     * @param char $variable
     * @param char $value
     * @return int
     */
    public function uciAddList( $uuid, $variable, $value):int{

        return $this->uci->uciAddList($uuid,$variable,$value);
    }


    /**
     * @param char $uuid
     * @param char $variable
     * @param char $value
     * @return int
     */
    public function uciDeleteList( $uuid, $variable, $value):int{

        return $this->uci->uciDeleteList($uuid,$variable,$value);
    }

    /**
     * @param char $uuid
     * @param char $variable
     * @return int
     */
    public function uciDropList( $uuid, $variable):int{

        return $this->uci->dropList($uuid,$variable);
    }


    /**
     * @param char $request
     * @return array
     */
    public function uciGetListe( $request): array{

        $retour=$this->uci->uciGetListe($request);
        //on doit retourner un array
        $retour=[];
        do {
            $retour[]=FFI::string($retour->value);
        } while ($retour->Next!=null);

        return $retour;
    }


    /**
     * @param char $searchObject
     * @return int
     */
    public function uciModuleExiste( $searchObject):int{

        return $this->uciModuleExiste($searchObject);
    }

    /**
     * @param char $uuid
     * @return int
     */
    public function uciCommitModule( $uuid):int{

        return $this->uci->uciCommitModule($uuid);
    }

    public function UciReadModule(){

        return $this->uci->UciReadModule();
    }


    public function isArchived($uuid){
        return $this->uci->isArchived($uuid);
    }

    public function setArchived($uuid){
        return $this->uci->setArchived($uuid);
    }

    public function unsetArchived($uuid){
        return $this->uci-unsetArchived($uuid);
    }


    /****************************************************************************
    FONCTION:  isDiscovered

    But : PErmet de savoir a l'ihm si le module/capteur a ete declare vu

    Entr▒e : uuid du module
    Sortie : 1 deja vu et 0 jamais 'discovered'

    Derni▒me modification :  06/07/2020 par  PHD

     ****************************************************************************/
    public function isDiscovered($uuid) :bool {
        return $this->uci->isDiscovered($uuid);
    }

    /****************************************************************************
    FONCTION:  Discovered

    But :  declare vua le module (pour l'ihm)

    Entr▒e : uuid du module
    Sortie : 1 on a bien déclaré le module comme discovered
    0 erreur on a pas réussi a accéder aux UCI
    Derni▒me modification :  06/07/2020 par  PHD

     ****************************************************************************/
    public function discovered($uuid):bool {
        return $this->uci->Discovered($uuid);
    }


    public function isUp($char){

        return $this->uci->isUp($char);
    }

    public function nbCapteur($char,$type){

        return $this->uci->nbCapteur($char,$type);
    }

    public function getValues($mac,$type,$index){

        $value=$this->uci->new("value_t");
        $retour=$this->uci->getValues($mac,$type,$index,$value);
        $ret=new \stdClass();
        $ret->retour=$retour;
        $ret->value=FFI::string($value);
        return $ret;

    }


    public function setOffset($mac,$type,$index){
        $values=$this->uci->new("value_t");
        return $this->uci->setOffset($mac,$type,$index,$values);

    }

    public function getOffset($uuid,$type,$index){


        return $this->uci->getOffset($uuid,$type,$index);
    }

}


?>
