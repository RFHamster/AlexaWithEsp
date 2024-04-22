package com.robotica.bloqueadorAutomotivo.resources;

import java.util.List;
import java.util.Map;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.robotica.bloqueadorAutomotivo.entities.Consulta;
import com.robotica.bloqueadorAutomotivo.entities.User;
import com.robotica.bloqueadorAutomotivo.services.ConsultaService;

@RestController
@RequestMapping(value="/consultas")
public class ConsultaResource {
	@Autowired
	private ConsultaService service;
	
	@GetMapping
	public ResponseEntity<List<Consulta>> findAll(){
		List<Consulta> list = service.findAll();
		return ResponseEntity.ok().body(list);
	}
	
	@PostMapping("/")
	public ResponseEntity<Consulta> saveConsulta(@RequestBody Map<String,String> c){
		Consulta consulta = service.saveConsulta(Long.parseLong(c.get("userId")), c.get("mensagem"),c.get("dataConsulta"));
		return ResponseEntity.ok().body(consulta);
	}
	
	@PostMapping("/userId")
	public ResponseEntity<Consulta> findByIdUsuario(@RequestParam Long id){
		Consulta list = service.findByIdUsuario(id);
		return ResponseEntity.ok().body(list);
	}
	
	@PostMapping("/user")
	public ResponseEntity<Consulta> findByUsuario(@RequestParam User user){
		Consulta list = service.findByUsuario(user);
		return ResponseEntity.ok().body(list);
	}
	
	@GetMapping(value="/{id}")
	public ResponseEntity<Consulta> findById(@PathVariable Long id){
		Consulta consulta = service.findById(id);
		if (consulta == null) {
			return ResponseEntity.status(HttpStatus.NOT_FOUND).build();
	    }
		return ResponseEntity.ok().body(consulta);
	}
}
