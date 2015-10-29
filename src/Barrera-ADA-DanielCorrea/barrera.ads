with GNAT.IO;  use GNAT.IO;
package barrera is
   type barreraAbstracta(tamano: Integer) is limited private;
   procedure sincronizarBarrera(b : in out barreraAbstracta);

   private
   protected type barreraAbstracta(tamano: Integer) is
      procedure entrar;
      entry wait;
   private
      contador : Integer := 0;
      tamanoBarrera : Integer := tamano;
   end barreraAbstracta;

end barrera;
