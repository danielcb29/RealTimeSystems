with Ada.Interrupts; use Ada.Interrupts;
with Ada.Interrupts.Names; use Ada.Interrupts.Names;

package controlador is
   protected ObjetoControlador is
      entry Wait;
      procedure Handle;
      pragma Interrupt_Handler(Handle);
      pragma Attach_Handler(Handle, Sigint);
      pragma Unreserve_All_Interrupts;
   private
      Call_Count : Natural := 0;
   end ObjetoControlador;

end controlador;
