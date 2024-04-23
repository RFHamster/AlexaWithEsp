package com.robotica.bloqueadorAutomotivo.resources;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

import com.robotica.bloqueadorAutomotivo.entities.Portas;
import com.robotica.bloqueadorAutomotivo.services.PortasService;

@RestController
@RequestMapping(value="/portas")
public class PortasResource {
	@Autowired
	private PortasService service;
	@GetMapping("/cadastrar")
    public Portas Cadastro(
            @RequestParam("chassi") String chassi,
            @RequestParam("tipo") String tipo,
            @RequestParam("nome") String nome,
            @RequestParam("porta") String porta) {
		Integer c = Integer.valueOf(chassi);
		return service.savePortas(nome, tipo, porta, c);
    }
	
	@GetMapping("/chassi/{chassi}")
    public ResponseEntity<List<Portas>> findByChassi(
            @PathVariable("chassi") Integer chassi) {
		Integer c = Integer.valueOf(chassi);
        List<Portas> list = service.findByIdChassi(c);

        return ResponseEntity.ok().body(list);
    }
}
