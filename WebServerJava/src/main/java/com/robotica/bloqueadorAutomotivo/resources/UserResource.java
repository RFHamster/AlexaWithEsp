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
import org.springframework.web.bind.annotation.RestController;

import com.robotica.bloqueadorAutomotivo.entities.User;
import com.robotica.bloqueadorAutomotivo.services.UserService;

@RestController
@RequestMapping(value="/users")
public class UserResource {
	
	@Autowired
	private UserService service;
	
	@GetMapping
	public ResponseEntity<List<User>> findAll(){
		List<User> list = service.findAll();
		return ResponseEntity.ok().body(list);
	}
	
	@PostMapping("/login")
    public ResponseEntity<User> login(@RequestBody Map<String, String> parametro) {
		String username = parametro.get("username");
		String password = parametro.get("password");
		System.out.println(username + " " + password);
        System.out.println("User " + username + " e password " + password);
		User user = service.findByUsuario(username);
        
        if (user == null) {
        	return ResponseEntity.status(HttpStatus.NOT_FOUND).build();
        }
        if(!user.getSenha().equals(password)){
        	return ResponseEntity.status(HttpStatus.UNAUTHORIZED).build();
        }
        return ResponseEntity.ok(user);

    }
	
	@GetMapping(value="/{id}")
	public ResponseEntity<User> findById(@PathVariable Long id){
		User user = service.findById(id);
		if (user == null) {
			return ResponseEntity.status(HttpStatus.NOT_FOUND).build();
	    }
		return ResponseEntity.ok().body(user);
	}
	
}
