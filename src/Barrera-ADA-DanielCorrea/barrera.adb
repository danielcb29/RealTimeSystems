package body barrera is
   procedure sincronizarBarrera(b: in out barreraAbstracta) is begin
      b.entrar;
      b.wait;
   end sincronizarBarrera;

   protected body barreraAbstracta is
      procedure entrar is begin
         Put_Line  ("Entrando a la barrera");
         contador := contador +1;
      end;

      entry wait when contador = tamanoBarrera is begin
         Put_Line  ("Saliendo de la barrera");
      end;

   end barreraAbstracta;

end barrera;
