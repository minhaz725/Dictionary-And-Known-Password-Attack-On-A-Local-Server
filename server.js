const express = require('express')
const app = express()
const bcrypt = require('bcrypt')

app.use(express.json())

const users = []

app.get('/users' , (req, res) => {
    res.json(users)
})

app.post('/users' , async (req, res) => {
    try {
        const hashedPass = await bcrypt.hash(req.body.password, 10) 
        const user = {
            name: req.body.name,
            password: hashedPass
        }
        
        users.push(user)
        res.status(201).send()
    } catch (error) {
    res.status(500).send()
        
    }
    
})

app.post('/users/login' , async (req, res) => {
    const user = users.find(user => user.name === req.body.name)
    if (user == null) {
        return res.status(400).send('User not found')
    }
    try {
        if (await bcrypt.compare(req.body.password, user.password)) {
            res.status(200).send('Success')
        }
        else {
            res.status(403).send('Not Allowed')
        }
    } catch (error) {
    res.status(500).send()
        
    }
    
})

app.listen(3000)