with barrera; use barrera;
procedure Main is
   entrada: aliased barreraAbstracta(10);
   type punteroBarrera is access all barreraAbstracta;

   task type lanzarTareas(Puntero: punteroBarrera);
   task body lanzarTareas is begin
     sincronizarBarrera(Puntero.all);
   end;

   type tareasIn is array (1..10) of lanzarTareas(entrada'Access);
   arregloIn : tareasIn;
begin
   --  Insert code here.
   null;
end Main;
